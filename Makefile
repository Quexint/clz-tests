CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = clz_iter clz_recur clz_bsearch clz_byteshift clz_harley
all: $(EXEC)

SRCS_common = main.c

all: $(EXEC)


clz_iter: $(SRCS_common) clz_iter.c clz_iter.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -g -o $@ \
		$(SRCS_common) $@.c

clz_recur: $(SRCS_common) clz_recur.c clz_recur.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -g -o $@ \
		$(SRCS_common) $@.c

clz_bsearch: $(SRCS_common) clz_bsearch.c clz_bsearch.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -g -o $@ \
		$(SRCS_common) $@.c

clz_byteshift: $(SRCS_common) clz_byteshift.c clz_byteshift.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -g -o $@ \
		$(SRCS_common) $@.c

clz_harley: $(SRCS_common) clz_harley.c clz_harley.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -g -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./clz_iter && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./clz

#output.txt: cache-test calculate
#	./calculate
#
#plot: output.txt
#	gnuplot scripts/runtime.gp
#
#calculate: calculate.c
#	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png
