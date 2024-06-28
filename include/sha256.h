#ifndef SHA256_H
# define SHA256_H

#include "utils.h"

# define ROTATE_RIGHT_32(a,b) (((a) >> (b)) | ((a) << (32-(b))))

typedef struct {
	uint32_t	state[8];
	uint64_t	size;
	uint8_t		buffer[64];
	uint8_t		digest[32];
} sha256_ctx;


char*   sha256_file_func(int fd, uint8_t *result);
void    sha256_str_func(const uint8_t *input, size_t input_size, uint8_t *result);
#endif