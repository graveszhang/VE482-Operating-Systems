# LemonDB

**Group 4**

* Liqin Zhang, 517370910123, graves_zhang@sjtu.edu.cn
* Siwei Ye, 517370910122, swayye@sjtu.edu.cn
* Yuao Yang, 517021910098, yangyuao@sjtu.edu.cn
* Yuelin Liu, 517370910252, liuyuelin@sjtu.edu.cn

## Introduction

"LemonDB" is a simple database management system based on its remaining code. We first implemented the single threaded version of the basic function described in the manual section of [p2](https://umjicanvas.com/courses/1826/files/folder/projects), and then we developed a muti-threaded query processing function to speed up the project. We made several serious benchmark under various query scenes to test its performance and we found that it speed has been improved overall. 

## Using Guideline

1. Download our source code from release.
```bash
unzip Archive.zip
```

2. Use CMake to compile and make the project.

   ```bash
   mkdir cmake && cd cmake
   cmake ./
   make
   ```

3. LemonDB supports two modes of input: `stdin` and `listen`.

   For `stdin`,  the user run the binary program `./lemondb` without any argument, and then It will ask the user to type in queries one by one in the console.

   For listen, the user run  `./lemondb --listen <filename> --thread <int>` , which takes the queries from `<filename>` and use  `<int>` number of threads to run. If `<int>` equals 0, the program will auto-detect the number of cores on the machine and use all of them.

4. Regarding specific usage of queries, it is described detailly in section 4 and 5 of [p2](https://umjicanvas.com/courses/1826/files/folder/projects).

## Design

### File Structure

[![D82kuD.png](https://s3.ax1x.com/2020/11/22/D82kuD.png)](https://imgchr.com/i/D82kuD)

-  `src/` folder is the main folder, which includes `main.cpp` for top layer user interface and I/O management, `CMakeLists.txt` for building project and compilation. It also contains all the sub-folders and the belonging files.
-  `src/db` folder contains files that initialize the database and the tables.
-  `src/query` includes files that are responsible for query parsing, query classification and query output. 
-  `src/query/data` is for table-level queries (e.g. `ADD`, `SELECT`).
-  `src/query/management` is for database-level queries (e.g. `COPY`, `DUMP`, `QUIT`)
-  `src/utils/` contains files that manage read, write and multi-threading.

### Work Flow

[![D8fvM6.png](https://s3.ax1x.com/2020/11/22/D8fvM6.png)](https://imgchr.com/i/D8fvM6)

* Regardless the input type (listen or stdin), one query will always go through the read-parse-execute loop.
* When reading queries, LemonDB takes a `;` symbol as the end of a query
* During the parse stage, LemonDB separate the query string into tokens according to space symbol and then check whether the syntax is valid.
* After the parse stage, the query will be executed and the result will be stored and outputted.
* Some special signal (EOF or Quit) will be checked to decide when LemonDB shall exit.

### Multi-threading

Among all the queries, some operations (e.g. `SELECT`, `SUM`, `COUNT`) must traverse the whole table, which becomes time consuming when the table has a large size. The main idea of the multi-threading in the LemonDB is to cut the table into several sub-tables. The number of sub-tables depends on the number of accessible threads. Then the operation can by greatly accelerated by distributing sub-tables to the available threads.  

[![D8HAAK.png](https://s3.ax1x.com/2020/11/22/D8HAAK.png)](https://imgchr.com/i/D8HAAK)

The major advantage of our multi-threaded version is that those threads can run in parallel and all the availble threads will be initially created and waited at one thread pool, once a query comes in, all the availble threads can be assigned to the job, thus the speed of executing queries will be significantly optimized. Notice there will always be one master thread (which is no different from others) will parse the query in a while loop.

## Performance Improvements

* We split the table into several sub-tables, and therefore accelerate the program by applying the current available threads to the query operations (e.g. `SELECT`, `SUM`, `COUNT`). These implementation should suit the database with large input size, especially for those large tables. We take the advantatge of available threads, initialize each iterator in a thread with its hash value in the table and combine the results once all the threads collect the correct result.

## Common Problems

* Critical Region and Locks

  How to protect the shared variables (or sth. else) during the multi-threading. In this project, we mainly utilizes two sets of mutex, one sets for reading, and the other sets are for writing. When queries are added to be parsed, we let several mutex within reading set run together, since there won't be any issue when working in parallel. However, to avoid the conflicts while writing, we have to let all writing mutex of different threads run in First-In First-Out manner, which admittedly limits the performance.
  
* For further improvements, the future LemonDB developers can focus on the efficiency of organizing the operations by columns (features). Now that we have split the table into several pieces for operation that requires a single query throughout the table, it is very likely that some of the query operation does not require the same features of each object in the table. We think it is a better solution if we could combine the two methods in query operations.

* Another aspect that could be optimized is that we could classify these operaitons into different categories. It is workable that the edit operation (e.g. `INSERT`, `DELETE`, `DUPLICATE` ) could be regarded as the parallel operations in the process end at the query operations since they have changed the list. As for query operation (e.g. `SELECT`, `SUM`, `COUNT`), they could be regarded as barrier in the process and wait for all the other threads to be released.

## Discussion and Conclusion

In this multi-threaded database system, we designed and implemented a relatively straightforward strategy to create a thread pool maximizing all the available threads - 1. The stand alone thread is used for parsing the query, while all left others will work in parallel to handle the queries in the query pool. We also created a hash mapping for selecting values from the table, we create the iterator to traversing the table instead of using for loop. This technique will help us saves at least five times speed comparing to the single threaded version.

In the near future, as always, we Lemonion, Inc. will work on how to horizontally split the queries so that we can allocate different tasks from the single query to multiple available threads. This upcoming update will make threads work more efficiently and smartly, until then, we hope you can enjoy our current release. Thanks.
