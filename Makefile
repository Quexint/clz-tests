CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall
EXECUTABLE = \
	benchmark_clock_gettime

default: clz.o
	$(CC) $(CFLAGS) clz.o benchmark_clock_gettime.c -o benchmark_clock_gettime

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

gencsv: default
	echo "N Iter Recur BShift BSearch Harley"> result_clock_gettime.csv
	for i in `seq 1 20000`; do \
		printf "%d " $$i;\
		./benchmark_clock_gettime $$i; \
	done >> result_clock_gettime.csv

plot: default gencsv
	gnuplot runtime.gp

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv result_error_rate.csv *.png
