# File I/O - tee
Developed a small UNIX tee like command to experiement with UNIX file I/O API.

An exercise from the book "The Linux Programming Interface" by Michael Kerrisk.

## Usage:
```
$ my_tee [-a] [filename]

```
For example, below command with -a is used to append to file ls.log which contains output
of the ls command.
```
$ ls | ./my_tee -a ls.log
```
