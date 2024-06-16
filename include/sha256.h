#ifndef SHA256_H
# define SHA256_H
# include <stdio.h>
# include <stdint.h>
# include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

# define ROTATE_RIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
# define SHIFT_RIGHT(x, n) (x >> n)
# define XOR ^
# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

typedef struct {
	uint32_t	state[8];
	uint64_t	size;
	uint8_t		buffer[64];
	uint8_t		digest[32];
} sha256_ctx;


void    sha256_file(int fd, uint8_t *result);
void    sha256_string(const uint8_t *input, size_t input_size, uint8_t *result);
#endif