CFLAGS= -Wall -Werror -O0 -std=c89 -pedantic -pedantic-errors -ggdb

.ifdef BITARRAY_MACROS
CFLAGS+= -D BITARRAY_MACROS
.else
CFLAGS+= -D BITARRAY_IMPLEMENTATION
.endif

tests: test test_perform
	./test
	./test_perform

test: bitarray.h test.c
	$(CC)  $(CFLAGS) -o test test.c

test_perform: bitarray.h test_perform.c
	$(CC) $(CFLAGS) -o test_perform test_perform.c

clean:
	rm -f test test_perform

.PHONY: tests clean
