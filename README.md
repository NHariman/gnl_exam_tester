# gnl_exam_tester
A simple tester for the exam version of get_next_line
## How it works
Clone this repository

Copy your `get_next_line.c` into the repo

Execute `bash test.sh` in the folder.

The program will compile your gnl and compare it to an example gnl (mine, nhariman).
If there are differences found between outputs you will find a `differences.txt` file that you can examine (the diff will also be printed in the terminal)
(WARNING, I passed the exam but passing this test will probably not guarantee you will too, leaks and stuff.)

To check for leaks, do not run the bash file, but instead compile:
```
gcc -Wall -Werror -Wextra get_next_line.c leaks_main.c
```
And run your own test, ie.
```
./a.out < exam_main.c
```
This will give you an infinite while loop and you can check leaks using
```
leaks a.out
```
ON MAC (don't know how on linux sorry!!)

To do your own basic tests:
```
gcc -Wall -Werror -Wextra get_next_line.c exam_main.c
./a.out < [whatever file you want your gnl to print]
```
