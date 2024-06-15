#ifndef MD5_H
# define MD5_H
# include <stdio.h>
# include <stdint.h>
# include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
/* magic constants */
# define A_CONST 0x67452301
# define B_CONST 0xefcdab89
# define C_CONST 0x98badcfe
# define D_CONST 0x10325476
# define MAX_READ_BYTES 1024
# define MAX_CHUNK_SIZE 64
# define CHUNK_NO_PADDING 56

/* bit-manipulation functions defined by the MD5 algorithm */
# define F(X, Y, Z) ((X & Y) | (~X & Z))
# define G(X, Y, Z) ((X & Z) | (Y & ~Z))
# define H(X, Y, Z) (X ^ Y ^ Z)
# define I(X, Y, Z) (Y ^ (X | ~Z))
# define FIRST_ROUND 1
# define SECOND_ROUND 2
# define THIRD_ROUND 3
# define FORTH_ROUND 4
# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# define ROUND(i) ( \
	(i / 16) == 0 ? FIRST_ROUND :\
	(i / 16) == 1 ? SECOND_ROUND :\
	(i / 16) == 2 ? THIRD_ROUND :\
	0)

typedef struct {
	uint32_t	state[4];
	uint64_t	size;
	uint8_t		buffer[64];
	uint8_t		digest[16];
} md5_ctx;

void    md5_string(const uint8_t *input, size_t input_size, uint8_t *result);
void    md5_file(int fd, uint8_t *result);
void    print_bits(const uint8_t *msg, size_t len) ;

#endif