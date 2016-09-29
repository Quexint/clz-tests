CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall
EXECUTABLE = \
	benchmark_clock_gettime benchmark_error

default: clz.o
	$(CC) $(CFLAGS) clz.o benchmark_clock_gettime.c -o benchmark_clock_gettime
	$(CC) $(CFLAGS) clz.o benchmark_error.c -o benchmark_error

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

gencsv: default
	echo "N Iter Recur BShift BSearch Harley" > result_clock_gettime.csv
	./benchmark_clock_gettime 20000 >> result_clock_gettime.csv

plot: default gencsv
	gnuplot runtime.gp

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv *.png
