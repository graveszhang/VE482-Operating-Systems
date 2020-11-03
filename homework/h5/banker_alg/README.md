> Name: Liqin Zhang
>
> UID: 517370910123

## VE482 Homework 5

### Banker's Algorithm Implementation

This is my implementation for banker's algorithm, I define a class for each process, which records the information like its requirements to resources, and if it has completed running. The ```printstat``` is a handful tool to check the information about each process.

```python
class process:
    def __init__(self):
        self.max = []
        self.allocation = []
        self.need = []
        self.completed = False

    def printstat(self):
        print("Max resources: ", str(self.max))
        print("Allocated resources: ", str(self.allocation))
        print("Need resources: ", str(self.need))
```



To demo its function, I created a sample input as is store in ```input```,  it has 4 process competing 3 types of resources at the same time. The explanation for each input line is given in comments. 

```bash
### First two line denotes basic information
4     	<- number of process
3		<- number of resource

### This is for process 1 initialization
3 2 2   <- max resouces for process 1
1 0 0   <- allocated resouces for process 1
2 2 2   <- needing resouces for process 1

### This is for process 2 initialization
6 1 3
5 1 1
1 0 2

### This is for process 3 initialization
3 1 4
2 1 1
1 0 3

### This is for process 4 initialization
4 2 2
0 0 2
4 2 0
1 1 2
```

### Sample Output

```python
Initialization Completed!
process_num: 4
resource_num: 3
available resource: [1, 1, 2]
------ Process 0 Status -------
Max resources:  [3, 2, 2]
Allocated resources:  [1, 0, 0]
Need resources:  [2, 2, 2]
------ Process 1 Status -------
Max resources:  [6, 1, 3]
Allocated resources:  [5, 1, 1]
Need resources:  [1, 0, 2]
------ Process 2 Status -------
Max resources:  [3, 1, 4]
Allocated resources:  [2, 1, 1]
Need resources:  [1, 0, 3]
------ Process 3 Status -------
Max resources:  [4, 2, 2]
Allocated resources:  [0, 0, 2]
Need resources:  [4, 2, 0]
------ Banker's Algorithm ------
Status: safe
```

### Usage

For your convenience, you can directly use my provided sample input as 

```bash
python main.py < input
```

Or you can use your own parameters by typing as the format I have given above.
