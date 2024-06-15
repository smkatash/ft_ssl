#ifndef UTILS_H
#define UTILS_H

# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# define MAX_READ_BUFFER_SIZE 1024

void	bytes_to_32bit_words_little_endian(uint32_t *dest, const void *src, size_t max_len);
void	bytes_to_32bit_words_big_endian(uint32_t *dest, const void *src, size_t max_len);
void	bytes_from_32bit_words_little_endian(uint8_t *dest, const void *src, size_t max_len);
void    bytes_from_32bit_words_big_endian(uint8_t *dest, const void *src, size_t max_len);
void    to_big_endian(uint8_t *dst, const void *src, size_t len);
void    print_bits(const uint8_t *msg, size_t len);

#endif