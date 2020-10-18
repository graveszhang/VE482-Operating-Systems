> Arthor: Liqin Zhang
>
> UID: 517370910123
>
> VE482 Homework3

## Compile

The code is written in c, and tested under macOS Catalina 10.15.4. 

Please use following command to compile and run the code (make sure cmake is installed).

```c
cmake ./
```

## Usage

This project is my implementation of a comparator based on the linked list data structure, it takes a ASCII plaintext message as input and generate a file with regard to the specification soring order. 

The input format for the first parameter is shown as follows, which shows the content in that file.

- rand_int.txt
- rand_double.txt
- rand_string.txt

The second input parameter represents the increasing, decreasing and random order of the output:

- inc
- dec
- rand

A sample output of this program is given below:

```bash
## ./h3 rand_int.txt inc
reading rand_int.txt
sorting elements
writing inc_int.txt

## cat rand_int.txt
bac=234
acb=148
ghi=9

## cat inc_int.txt
ghi=9
acb=148
bac=234
```