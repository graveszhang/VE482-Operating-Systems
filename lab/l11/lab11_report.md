> Name: 
>
> Liqin Zhang 517370910123
>
> Siwei Ye 517370910122

# Lab 11 FUSE

## Tasks

- What is a filesystem?

  In computing, a **file system** or **filesystem** (often abbreviated to fs) controls how data is stored and retrieved. By separating the data into pieces and giving each piece a name, the data is easily isolated and identified. Taking its name from the way paper-based data management system is named, each group of data is called a "file." The structure and logic rules used to manage the groups of data and their names is called a "file system."

- How is the Linux VFS working?

  In Linux, all files are accessed through the Virtual Filesystem Switch, or VFS. This is a layer of code which implements generic filesystem actions and vectors requests to the correct specific code to handle the request.

  The source code for the VFS is in the fs/ subdirectory of the Linux kernel source, along with a few other related pieces, such as the buffer cache and code to deal with each executable file format. Each specific filesystem is kept in a lower subdirectory; for example, the ext2 filesystem source code is kept in fs/ext2/.

- What is FUSE, and how does it interact with the VFS? Can you sketch it quickly to make it clearer?

  **Filesystem in Userspace (FUSE)** is a software interface for Unix and Unix-like computer operating systems that lets non-privileged users create their own file systems without editing kernel code.

  Here’s a flow-chart diagram showing how FUSE works, source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:FUSE_structure.svg)

  ![img](https://engineering.facile.it/images/write-filesystem-fuse/FUSE_structure.svg)

  When a filesystem related process is created (e.g. `ls -l /tmp/fuse `), the virtual filesystem in the kernel level interact with FUSE and let FUSE call the corresponding program (`./hello /tmp/fuse`) with `libfuse`, then return the contents back to VFS, and show the result.

## Implementation

### Install dependency

```bash
apt-get install fuse libfuse-dev
```

### Locate the hidden file

After downloading from ji-git, we found a file named ```.del```

Open the file use ```cd .del && ll```

Then we found all the selecton codes and other files  as follows.

```bash
drwxrwxr-x@ 6 gravescn  staff    192 Dec  2 23:15 .
drwxrwxr-x@ 4 gravescn  staff    128 Dec  2 15:54 ..
-rw-rw-r--@ 1 gravescn  staff  12288 Nov 30 21:28 .lemondbfs.c.swp
-rw-rw-r--@ 1 gravescn  staff    294 Dec 23  2017 Makefile
-rw-rw-r--@ 1 gravescn  staff   2445 Oct 18  2018 README
```

### Recover the file

To recover `lemondbfs.c` from `.lemondbfs.c.swp`, run

```bash
vim -r .lemondbfs.c.swp
```

And then we can reveal the original(failed) code file 

```bash
-rw-rw-r--@ 1 gravescn  staff   4722 Dec  2 23:05 lemondbfs.c
```

### Rewrite lemondbfs

See `lemondbfs.c`

### Build

```bash
make
```



