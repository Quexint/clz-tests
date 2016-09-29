#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clz.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

static double diff_in_second(struct timespec start, struct timespec end)
{
    return (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
}

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    double cpu_time1;
    int LOOP = 500;
    double *sav = (double*)malloc(sizeof(double)*(N+3)*5);

    // iter
    for(int i = 1; i <= N; i++) {
        clock_gettime(CLOCK_ID, &start);
        for(int j = 0; j < LOOP; j++)
            clz_iter(i);
        clock_gettime(CLOCK_ID, &end);
        cpu_time1 = diff_in_second(start, end);
        sav[5*i + 0] = cpu_time1;
    }

    // recur
    for(int i = 1; i <= N; i++) {
        clock_gettime(CLOCK_ID, &start);
        for(int j = 0; j < LOOP; j++)
            clz_recur(i);
        clock_gettime(CLOCK_ID, &end);
        cpu_time1 = diff_in_second(start, end);
        sav[5*i + 1] = cpu_time1;
    }

    // byte_shift
    for(int i = 1; i <= N; i++) {
        clock_gettime(CLOCK_ID, &start);
        for(int j = 0; j < LOOP; j++)
            clz_byteshift(i);
        clock_gettime(CLOCK_ID, &end);
        cpu_time1 = diff_in_second(start, end);
        sav[5*i + 2] = cpu_time1;
    }

    // bsearch
    for(int i = 1; i <= N; i++) {
        clock_gettime(CLOCK_ID, &start);
        for(int j = 0; j < LOOP; j++)
            clz_bsearch(i);
        clock_gettime(CLOCK_ID, &end);
        cpu_time1 = diff_in_second(start, end);
        sav[5*i + 3] = cpu_time1;
    }

    // harley
    for(int i = 1; i <= N; i++) {
        clock_gettime(CLOCK_ID, &start);
        for(int j = 0; j < LOOP; j++)
            clz_bsearch(i);
        clock_gettime(CLOCK_ID, &end);
        cpu_time1 = diff_in_second(start, end);
        sav[5*i + 4] = cpu_time1;
    }

    for(int i = 1; i <= N; i++)
        printf("%d %.7lf %.7lf %.7lf %.7lf %.7lf\n", i, sav[5*i], sav[5*i+1], sav[5*i +2], sav[5*i +3], sav[5*i+4]);
    return 0;
}
