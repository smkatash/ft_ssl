#ifndef SHA512_H
# define SHA512_H

#include "utils.h"

# define SHA512_CHUNK_SIZE 128
# define SHA512_CHUNK_NO_PADDING  SHA512_CHUNK_SIZE - 16 // 128-bit length - 2 bytes

#define ROTATE_RIGHT_64(x, n) ((x >> n) | (x << (64 - n)))

typedef struct {
	uint64_t	state[8];
	uint64_t	size;
	uint8_t		buffer[SHA512_CHUNK_SIZE];
	uint8_t		digest[64];
} sha512_ctx;


char*   sha512_file_func(int fd, uint8_t *result);
void    sha512_str_func(const uint8_t *input, size_t input_size, uint8_t *result);
#endif