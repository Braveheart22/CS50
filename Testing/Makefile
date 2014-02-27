#
# Makefile
#
# Computer Science 50
# Problem Set 4
#

GDB-testing: GDB-testing.c Makefile
	clang -ggdb3 -Ispl/include -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o GDB-testing GDB-testing.c -Lspl/lib -lm

clean:
	rm -f *.o core breakout
