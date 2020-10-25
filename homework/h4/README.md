> ID: 517370910123
>
> Name: Liqin Zhang
>
> Mail: graves_zhang@sjtu.edu.cn

## VE482 Homework 4

### 3. Racing condition in Bash

```racing.sh``` is used to illustrate a racing condition. When running alone, the output seems fine.

```bash
./racing.sh
cat text.txt ## Output 0-100
```

However, when running it in background and foreground, multiple processes are sharing resources, thus the output become messy.

```bash
./racing.sh & ./racing.sh
cat text.txt ## This generates messy integer sequence
```

```flock.sh``` utilizes the linux package ```flock```, which allows locking the process while running to prevent other access.  
```bash
./flock.sh & ./flock.sh
cat text.txt ## Works fine again
```

