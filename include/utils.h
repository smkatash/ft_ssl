#ifndef UTILS_H
#define UTILS_H

# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"
# define MAX_READ_BUFFER_SIZE 1024
# define CHUNK_NO_PADDING 56
# define MAX_CHUNK_SIZE 64

void	bytes_to_32bit_words_little_endian(uint32_t *dest, const void *src, size_t max_len);
void	bytes_to_32bit_words_big_endian(uint32_t *dest, const void *src, size_t max_len);
void	bytes_from_32bit_words_little_endian(uint8_t *dest, const void *src, size_t max_len);
void    bytes_from_32bit_words_big_endian(uint8_t *dest, const void *src, size_t max_len);

#endif