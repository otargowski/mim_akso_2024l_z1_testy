.PHONY: clean clean_fr_fr all format run run_duzo fetch fetch_duzo
# (GNU?) make moment (maybe add `.CLOWN: make`?)
.PRECIOUS: %.zst

BUILD_TYPE ?= release
CC = gcc
# -O2 is added if BUILD_TYPE isn't set to debug.
CXXFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=c++20 -fPIC
CLANG_FORMAT_STYLE = {BasedOnStyle: Microsoft, ColumnLimit: 80, \
	BreakBeforeBraces: Attach}


ifeq ($(BUILD_TYPE),debug)
	CXXFLAGS += -Wshadow -Wconversion -ggdb3 -fsanitize=address,undefined -O0 \
			  -Wformat=2 -Wfloat-equal -Wlogical-op -Wduplicated-cond \
			  -Wcast-qual -Wcast-align
else
	CXXFLAGS += -O2
endif

all: run run_duzo

ma_test: ma_test.o ../libma.so
	g++ -L.. ma_test.o -lma -o $@ $(CXXFLAGS) 

ma_gen: ma_gen.o
	g++ ma_gen.o -o $@ $(CXXFLAGS) 

# Generated with `gcc -MM *.cpp`
ma_gen.o: ma_gen.cpp
ma_test.o: ma_test.cpp ../ma.h ../memory_tests.h

%.zst:
	curl -LO https://students.mimuw.edu.pl/~ot469694/akso/z1/$@

%.in: %.in.zst
	zstd -d -T0 $@.zst

%.out: %.out.zst
	zstd -d -T0 $@.zst

fetch: malo.in malo.out srednio.in srednio.out

fetch_duzo: duzo.in duzo.out

run: ma_test fetch
	LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:.." ./ma_test < malo.in > malo.out.new
	diff malo.out malo.out.new
	LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:.." ./ma_test < srednio.in > srednio.out.new
	diff srednio.out srednio.out.new

run_duzo: ma_test fetch_duzo
	LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:.." ./ma_test < duzo.in > duzo.out.new
	cmp duzo.out duzo.out.new

format:
	clang-format -i --style="$(CLANG_FORMAT_STYLE)" *.cpp

clean:
	rm -f *.o ma_test ma_gen *.in *.out *.new

clean_fr_fr: clean
	rm -f *.zst
