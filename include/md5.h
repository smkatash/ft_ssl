#ifndef MD5_H
# define MD5_H

#include "utils.h"
/* magic constants */
# define A_CONST 0x67452301
# define B_CONST 0xefcdab89
# define C_CONST 0x98badcfe
# define D_CONST 0x10325476

/* bit-manipulation functions defined by the MD5 algorithm */
# define F(X, Y, Z) ((X & Y) | (~X & Z))
# define G(X, Y, Z) ((X & Z) | (Y & ~Z))
# define H(X, Y, Z) (X ^ Y ^ Z)
# define I(X, Y, Z) (Y ^ (X | ~Z))
# define FIRST_ROUND 1
# define SECOND_ROUND 2
# define THIRD_ROUND 3
# define FORTH_ROUND 4

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

void    md5_str_func(const uint8_t *input, size_t input_size, uint8_t *result);
char	*md5_file_func(int fd, uint8_t *result);

#endif