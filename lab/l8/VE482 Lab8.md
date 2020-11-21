> Name: 
>
> Liqin Zhang 517370910123
>
> Siwei Ye 517370910122

## VE482 Lab8

### Memory management at kernel level

- What does vm stands for? (Hint: in this context the answer is not virtual machine) 

  ```vm``` stands for virtual memory.

- Find all the places where the vm used inside the kernel. Why does it appear in so many different 

  places? 

  We find that the structure used by VM to pass data to the kernel while enabling paging is defined in ```/include/arch/arm/include/vm.h```.  It also includes the memory part of PM. (`fork()`, `exit()`) 

  All files under ```/servers/vm/``` use ```vm```. It is used when we need to run one or several programs using large amount of mem. Since there is not enough space in RAM, we can use VM to let the program imagine they have enough memory (in fact we are partially using disk space), thus helping the program to complete. 

- How is memory allocated within the kernel? Why are not malloc and calloc used? 

  We use ```kmalloc``` or ```vmalloc``` in kernel,   `calloc` and `malloc` both requires the package `stdlib.h`, which can only be accessed from the user space.

- While allocating memory, how does the functions in kernel space switch back and fro between user and kernel spaces? How is that boundary crossed? How good or bad it is to put vm in userspace? 

  There are two ways. Message passing(mainly) and memory grants (for transferring larger amount of data).

  The message is mainly composed of 

  - Endpoint: who is sending the message? e.g. ```VM_PROC_NR``` .
  - Type: What is the message about? e.g. ```VM_PAGEFAULT``` .
  - Other data 

  There are three basic APIs: 

  1. SEND: a message is sent, the sender is blocked until the message is delivered. 

  2. RECEIVE: the process is blocked until a message is delivered to them, 

  3. SENDEREC: a message is sent, the sneder is blocked until reply from the receiver 

  The boundary is crossed using ```brk``` system call. It is bad consider putting ```vm``` in user space, as the idea of creating virtual space (usually hard disk) for the memory, each time we need to call ```vm```, we have to cross the boundary, which is very resource consuming and dangerous considering the malicious attack from outside sources.

- How are pagefaults handled? [^1][^2]

  1. The computer hardware traps to the kernel and program counter (PC) is saved on the stack. Current instruction state information is saved in CPU registers.
  2. An assembly program is started to save the general registers and other volatile information to keep the OS from destroying it.
  3. Operating system finds that a page fault has occurred and tries to find out which virtual page is needed. Sometimes hardware register contains this required information. If not, the operating system must retrieve PC, fetch instruction and find out what it was doing when the fault occurred.
  4. Once virtual address caused page fault is known, system checks to see if address is valid and checks if there is no protection access problem.
  5. If the virtual address is valid, the system checks to see if a page frame is free. If no frames are free, the page replacement algorithm is run to remove a page.
  6. If frame selected is dirty, page is scheduled for transfer to disk, context switch takes place, fault process is suspended and another process is made to run until disk transfer is completed.
  7. As soon as page frame is clean, operating system looks up disk address where needed page is, schedules disk operation to bring it in.
  8. When disk interrupt indicates page has arrived, page tables are updated to reflect its position, and frame marked as being in normal state.
  9. Faulting instruction is backed up to state it had when it began and PC is reset. Faulting is scheduled, operating system returns to routine that called it.
  10. Assembly Routine reloads register and other state information, returns to user space to continue execution.

  [^1]:[cs.uttyler.edu](http://cs.uttyler.edu/Faculty/Rainwater/COSC3355/Animations/pagefaultsteps.htm)
  [^2]:[professormerwyn.wordpress.com](https://professormerwyn.wordpress.com/2015/10/16/steps-for-handling-page-fault/)

### Mum's really unfair

- What algorithm is used by default in Minix 3 to handle pagefault? Find its implementation and study it closely. 

  ```LRU``` implemented in ```/server/vm/region.c```.  Notice that it uses a LRU list to store various blocks, and always maintain a pointer to the youngest block and oldest block. The LRU list is a double-linked list, like what is shown below:

  ![image-20201121175021508](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l8/img/4.png)

  When the pagefault occurs, the oldest page will be removed and the pointer will be point to the next element in the list.

  ```c
  static void lrucheck(void)
  {
  	yielded_t *list;
  
  	/* list is empty and ok if both ends point to null. */
  	if(!lru_youngest && !lru_oldest)
  		return;
  
  	/* if not, both should point to something. */
  	SLABSANE(lru_youngest);
  	SLABSANE(lru_oldest);
  
  	assert(!lru_youngest->younger);
  	assert(!lru_oldest->older);
  
  	for(list = lru_youngest; list; list = list->older) {
  		SLABSANE(list);
  		if(list->younger) {
  			SLABSANE(list->younger);
  			assert(list->younger->older == list);
  		} else	assert(list == lru_youngest);
  		if(list->older) {
  			SLABSANE(list->older);
  			assert(list->older->younger == list);
  		} else	assert(list == lru_oldest);
  	}
  }
  ```

- Use the `top` command to keep track of your used memory and cache, then run `time grep -r "mum" /usr/src`. Run the command again. What do you notice? 

  Before running `time grep -r "mum" /usr/src`.

  ![image-20201121163134095](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l8/img/1.png)

  After running `time grep -r "mum" /usr/src.`

  ![image-20201121163222096](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l8/img/2.png)

  It can detected that when running `time grep -r "mum" /usr/src`, the `grep` command takes 356K memory and its CPU usage is 16.52%.

- Adjust the implementation of LRU into MRU and recompile the kernel. 

  To replace `LRU` with `MRU`, the function `free_yielded` in `region.c` is modified. I.e. free youngest node instead of oldest node in the list.

  ```diff
  /*========================================================================*
   *				free_yielded				  *
   *========================================================================*/
  vir_bytes free_yielded(vir_bytes max_bytes)
  {
  
  /* PRIVATE yielded_t *lru_youngest = NULL, *lru_oldest = NULL; */
  	vir_bytes freed = 0;
  	int blocks = 0;
  	
  +	while(freed < max_bytes && lru_youngest) {
  +		SLABSANE(lru_youngest);
  +		freed += freeyieldednode(lru_youngest, 1);
  -	while(freed < max_bytes && lru_oldest) {
  -		SLABSANE(lru_oldest);
  -		freed += freeyieldednode(lru_oldest, 1);
  		blocks++;
  	}
  
  	return freed;
  }
  ```

  Then recompile the kernel:

  ```bash
  su
  cd /usr/src
  make build
  ```

  

- Use the top command to keep track of your used memory and cache, then run time grep -r "mum" 

  /usr/src. Run the command again. What do you notice? 

  After recompilation, the result when running `time grep -r "mum" /usr/src` is shown below:

  ![image-20201121172612265](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l8/img/3.png)

  It can be detected that this time `grep` is taking more memory (400K) and more CPU usage (28.38%) .

- Discuss the different behaviours of LRU and MRU as well as the consequences for the users. Can 

  you think of any situation where MRU would be better than LRU? 

  In our above test, `MRU`  is worse than `LRU` because `grep` is recursively searching the contents in directory `/usr/src`. The memory accessed are close to each other in this command, which means during the search the page accessed are very likely to be accessed again in the future. If we use `MRU`, we freed the most recently accessed memory (youngest), then the frequency of page fault rapidly increases. 

  `MRU` would be better than `LRU` when the process the working on something that does not contain so much repeating.
