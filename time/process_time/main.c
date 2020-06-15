#include <unistd.h> // for sleep
#include <stdio.h>
#include <sys/times.h>
#include <time.h> // for clock and clock_t

int main(int argc, char *argv[])
{
    struct tms process_time;
    clock_t ticks_start, ticks_end, ticks_diff;
    clock_t clock_ticks;

    unsigned long ticks_per_sec = sysconf(_SC_CLK_TCK);

    ticks_start = times(&process_time);
    clock_ticks = clock();

    printf("Clock ticks: %lu, seconds: %.2f\n", clock_ticks, (double) clock_ticks / CLOCKS_PER_SEC);
    printf("User time: %.2f, system time: %.2f\n", (double) process_time.tms_utime / ticks_per_sec, 
                                                    (double) process_time.tms_stime / ticks_per_sec);
    unsigned long i;
    
    for (i = 0; i < 40000000; i++) {
        (void) getppid();;
    }

    ticks_end = times(&process_time);
    clock_ticks = clock();

    ticks_diff = ticks_end - ticks_start;

    printf("Total ticks: %lu, seconds: %.2f\n", ticks_diff, (double) ticks_diff / ticks_per_sec);
    printf("Clock ticks: %lu, seconds: %.2f\n", clock_ticks, (double) clock_ticks / CLOCKS_PER_SEC);
    printf("User time: %.2f, system time: %.2f\n", (double) process_time.tms_utime / ticks_per_sec, 
                                                   (double) process_time.tms_stime / ticks_per_sec);

    return 0;
}
