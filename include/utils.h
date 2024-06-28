#ifndef UTILS_H
#define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# define MAX_READ_BUFFER_SIZE 1024
# define CHUNK_NO_PADDING 56
# define MAX_CHUNK_SIZE 64

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# define SHIFT_RIGHT(x, n) (x >> n)
# define CH(x, y, z) ((x & y) ^ (~x & z))
# define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
# define XOR ^

void	bytes_to_32bit_words_little_endian(uint32_t *dest, const void *src, size_t max_len);
void	bytes_to_32bit_words_big_endian(uint32_t *dest, const void *src, size_t max_len);
void	bytes_to_64bit_words_big_endian(uint64_t *dest, const void *src, size_t max_len);
void    bytes_from_64bit_words_big_endian(uint8_t *output, const uint64_t *src, size_t len);
void	bytes_from_32bit_words_little_endian(uint8_t *dest, const void *src, size_t max_len);
void    bytes_from_32bit_words_big_endian(uint8_t *dest, const void *src, size_t max_len);
void    print_str_reversed(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_file_reversed(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_file(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_append_str(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_stdin(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_quiet(const char* input, uint8_t *cksm, size_t cksm_len);
void	print_str(const char *msg);
void	print_error(const char *msg, const char* err);
void	print_hex(uint8_t *p, size_t hash_len);


#endif