#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clz.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 200;

    // iter
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_iter(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // recur
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_recur(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // byte_shift
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_byteshift(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // bsearch
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_bsearch(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // harley
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_harley(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf\n", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    return 0;
}
