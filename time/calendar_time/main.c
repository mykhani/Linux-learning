
#define _XOPEN_SOURCE // for strptime()

#include <stdio.h>
#include <sys/time.h> // gettimeofday
#include <time.h>  // for time, clock_gettime
#include <stdlib.h>
#include <assert.h>
#include <unistd.h> //for sleep

void print_timeval(struct timeval* t)
{
    printf("Time (since epoch): %ld micro-seconds, %ld\n", t->tv_sec, t->tv_usec);

    return;
}

void print_time_t(time_t *t)
{
    printf("Time (since epoch): %lu seconds\n", *t); 
    
    return;
}

void test_gettimeoday_api()
{
    struct timeval now;

    printf("---------------------\n");
    printf("Testing gettimeofday \n");
    printf("---------------------\n");
    // tz field has been deprecated - see https://man7.org/linux/man-pages/man2/settimeofday.2.html
    assert(gettimeofday(&now, NULL) == 0);

    print_timeval(&now);

    printf("Adding 2s delay\n");
    sleep(2);
    
    assert(gettimeofday(&now, NULL) == 0);

    print_timeval(&now);

    return;
}

void test_time_api()
{
    time_t now;
    struct tm *gmp, *locp;
    struct tm input;
    struct tm gm, loc;
    char loc_fmt[256];

    printf("----------------------\n");
    printf("Testing time() \n");
    printf("----------------------\n");

    //assert(clock_gettime(CLOCK_MONOTONIC, &now) == 0); // CLOCK_MONOTONIC's reference point is not epoch
    assert((now = time(NULL)) != (time_t)-1);

    print_time_t(&now);

    printf("Adding 2s delay\n");
    sleep(2);
    
    assert((now = time(NULL)) != (time_t)-1);

    print_time_t(&now);

    printf("Time string: %s\n", ctime(&now));

    printf("Adding 2s delay\n");
    
    sleep(2);
    
    assert((now = time(NULL)) != (time_t)-1);
    
    printf("Time string: %s\n", ctime(&now));

    locp = localtime(&now);

    // save the local time as it could be modified by asctime() or gmtime()
    loc = *locp;
    gmp = gmtime(&now);
    gm = *gmp;

    printf("Local time: %s\n", asctime(&loc));
    printf("Global time: %s\n", asctime(&gm));

    assert(strftime(loc_fmt, sizeof(loc_fmt), "Date: %A %B %Y %H:%M", &loc) != 0);

    printf("Formatted time: %s\n", loc_fmt);

    strptime("Friday Jun 13:00", "%A %B %H:%M", &input);
    printf("Time from string: %s\n", asctime(&input));

    return;

}

int main(int argc, char *argv[])
{
    test_gettimeoday_api();
    test_time_api();
    
    return EXIT_FAILURE;
}
