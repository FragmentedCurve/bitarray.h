/*
 * Copyright (c) 2024, 2025 Paco Pascal <me@pacopascal.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
  This is a single header library providing a bit array data
  structure. It's implementation is very minimal and doesn't provide
  any form of safety. Branching is kept to a minimum.

  You may choose between two implementations, functions and
  macros. Obviously, functions have the benefit of type checking and
  being easier to debug. However, the macro implementation performs
  better.

  To use the function implementation, do

      #define BITARRAY_IMPLEMENTATION
      #include "bitarray.h"

  To use macros, do

      #define BITARRAY_MACROS
      #include "bitarray.h"

  Afterwards, you may create a bitarray. For example,

      bitarray_t* barr = malloc(bitarray_sizeof(128), sizeof(char));
      bitarray_on(barr, 64);

  will create a bit array with index range from 0 to 127, clear it,
  and set the 65th bit to 1. You're responsible for not going outside
  the boundaries.

  You may also abuse the underlying type for bitarray_t. By default,
  bitarray_t's underlying type is an unsigned char. If you wanted to
  enforce it to be an unsigned int, you can do the following,

      #define _BITARRAY_T unsigned int
      #define BITARRAY_IMPLEMENTATION
      #include "bitarray.h"
 */

/* TODO: Make a bloomfilter */

#ifndef _BITARRAY_H_
#define _BITARRAY_H_

#ifndef _BITARRAY_T
#define _BITARRAY_T unsigned char
#endif

#include <limits.h>
#define _BITARRAY_SIZE (CHAR_BIT * sizeof(_BITARRAY_T))
typedef _BITARRAY_T bitarray_t;

#ifdef BITARRAY_MACROS
#define bitarray_get(barr, index) \
	((int)(1 & ((barr)[(size_t)(index) / _BITARRAY_SIZE] >> ((size_t)(index) % _BITARRAY_SIZE))))
#define bitarray_on(barr, index) \
	((barr)[(size_t)(index) / _BITARRAY_SIZE] |= 1 << ((size_t)(index) % _BITARRAY_SIZE))
#define bitarray_off(barr, index) \
	((barr)[(size_t)(index) / _BITARRAY_SIZE] &= ~(1 << ((size_t)(index) % _BITARRAY_SIZE)))
#define bitarray_set(barr, index, value) \
	((value) ? bitarray_on((barr), (index)) : bitarray_off((barr), (index)))
#define bitarray_sizeof(n) \
	(sizeof(bitarray_t) * (((size_t)(n) / _BITARRAY_SIZE) + (0 < (n) % _BITARRAY_SIZE)))
#else
int bitarray_get(bitarray_t* barr, size_t index);
void bitarray_on(bitarray_t* barr, size_t index);
void bitarray_off(bitarray_t* barr, size_t index);
void bitarray_set(bitarray_t* barr, size_t index, int value);

#ifdef BITARRAY_IMPLEMENTATION
int
bitarray_get(bitarray_t* barr, size_t index)
{
	return 1 & (barr[index / _BITARRAY_SIZE] >> (index % _BITARRAY_SIZE));
}

void
bitarray_on(bitarray_t* barr, size_t index)
{
	barr[index / _BITARRAY_SIZE] |= 1 << (index % _BITARRAY_SIZE);
}

void
bitarray_off(bitarray_t* barr, size_t index)
{
	barr[index / _BITARRAY_SIZE] &= ~(1 << (index % _BITARRAY_SIZE));
}

void
bitarray_set(bitarray_t* barr, size_t index, int value)
{
	if (value) {
		bitarray_on(barr, index);
	} else {
		bitarray_off(barr, index);
	}
}

size_t
bitarray_sizeof(size_t bits)
{
	return sizeof(bitarray_t) * ((bits / _BITARRAY_SIZE) + (0 < (bits % _BITARRAY_SIZE)));
}
#endif /* BITARRAY_IMPLEMENTATION */
#endif /* BITARRAY_MACROS */
#endif /* _BITARRAY_H_ */
