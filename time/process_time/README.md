
## Linux measure process time
I am exploring two APIs for measuring process time.

* clock_t clock(void)
* clock_t times(struct tms \*t)

## Steps to compile and run

```
$ make
$ time ./process_time 
Clock ticks: 2944, seconds: 0.00
User time: 0.00, system time: 0.00
Total ticks: 985, seconds: 9.85
Clock ticks: 9841005, seconds: 9.84
User time: 4.05, system time: 5.78

real	0m9.856s
user	0m4.060s
sys	0m5.782s

```
