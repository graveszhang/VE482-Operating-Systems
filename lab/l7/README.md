> Liqin Zhang (517370910123) 
>
> Siwei Ye (517370910122)
>
> Nov 15 2020

## Dadfs Fixing Guide

0. Install independencies

- Check the kernel version of our own Ubuntu distribution.

```
uname -srf
```

The result we get is ```Linux 4.15.0-45-generic i686```

```
sudo apt-get install git
```

1. Compile

```
make
```

We spot one main error is about ```generic_write_checks``` when calling ```dadfs_write```, by looking up to bootlin, we find the usage of this function has changed in our kernel version[^dadwrite].

[^dadwrite]: https://elixir.bootlin.com/linux/v4.15/source/include/linux/fs.h#L2931

Next, we fix undeclared variable due to the different structure in function callings. For example, the following variable has to be re-linked:

- flip
- ppos
- len

Since we don't have ```struct iov_iter```, we need to include ```/linux/uio.h```

Next, we modify ```retval``` to let it formally use ```generic_write_checks```.

Finally, we add version control for ```.write``` and the compile is success!

![1](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/1.png)

2. create a small virtual disk (to be formated in dadfs): 

![2](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/2.png)

3. create a small virtual disk (to be used as dadfs' journal):

![3](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/3.png)

4. initialize the journal:

![4](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/4.png)

5. Format the disk

![5](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/5.png)

6. load dadfs module

![6](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/6.png)

7. mount disk

![7](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/7.png)

We can then use ```mount -l``` to check whether our dadfs has been correctly mounted.

![7-2](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/7-2.png)

Note that the last line denots that we have dadfs in ```/tmp```

8. play with dad filesystem

After a very casual testing for dadfs, we have the following initial findins:

- mv, cp doesn't work properly
- Tab key is not handled well -> it will cause the terminal freeze

- mkdir, cat, rm, ls, cd, touch seems fine.

![8](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/8.png)

- We've also found a word from dad...

![8-2](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/8-2.png)

9. check the logs

![9](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/9.png)

10. umount disk

![10](https://github.com/graveszhang/VE482-Intro-to-Operating-Systems/blob/master/lab/l7/img/10.png)

11. unload module

```bash
sudo rmmod dadfs.ko
```

