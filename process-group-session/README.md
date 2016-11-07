Linux process group and session
===============================
This is a sample code to show how the Linux process group and session work.
It consists of two programs, process1 and process2.

These programs are compiled and then run as below:

Running both processes by joining them via pipe.
```
$ ./process1 | ./process2 
process 1 with PID: 26349, Group ID: 26349, Session ID: 25456 
process 2 with PID: 26350, Group ID: 26349, Session ID:25456

$ ps  xao pid,ppid,pgid,sid,comm
  PID  PPID  PGID   SID COMMAND
    1     0     1     1 init
    2     0     0     0 kthreadd
    3     2     0     0 ksoftirqd/0
    5     2     0     0 kworker/0:0H
    7     2     0     0 rcu_sched

	*snip

25456  3051 25456 25456 bash ==> See session ID is set by bash terminal
```
* In the above log, both processes have same GID, set by the first process.
And the output of ps shows the Session ID is set by bash terminal process
as expected. 

* It shows that one different programs are executed via pipes
in bash, the first program is the process group leader and sets the group
ID to value of its own PID.

* It also shows that all processes run in the same shell has same session ID
set by shell process itself.


Now running the processes individually

```
$ ./process1 
process 1 with PID: 29230, Group ID: 29230, Session ID: 25456 
$ ./process2
adadasd
adadasd
process 2 with PID: 29231, Group ID: 29231, Session ID:25456 
```

See in the above log, both processes show different group IDs.
