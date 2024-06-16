#include "utils.h"

inline void	bytes_to_32bit_words_little_endian(uint32_t *dest, const void *src, size_t max_len)
{
	const uint8_t *src_bytes = (const uint8_t *)src;
	for (size_t j = 0; j < max_len; j++) {
		// fill up dest from src, each iter 4 bytes int0 32-bit words
		dest[j] = (uint32_t)(src_bytes[(j * 4) + 3]) << 24 |
			(uint32_t)(src_bytes[(j * 4) + 2]) << 16 |
			(uint32_t)(src_bytes[(j * 4) + 1]) <<  8 |
			(uint32_t)(src_bytes[(j * 4)]);
	}	
}

inline void	bytes_to_32bit_words_big_endian(uint32_t *dest, const void *src, size_t max_len)
{
	const uint8_t *src_bytes = (const uint8_t *)src;
	for (size_t j = 0; j < max_len; j++) {
		// fill up dest from src, each iter 4 bytes int0 32-bit words
		dest[j] = (uint32_t)(src_bytes[j * 4] << 24) |
			(uint32_t)(src_bytes[j * 4 + 1] << 16) |
			(uint32_t)(src_bytes[j * 4 + 2] <<  8) |
			(uint32_t)(src_bytes[j * 4 + 3]);
	}	
}

inline void	bytes_from_32bit_words_little_endian(uint8_t *dest, const void *src, size_t max_len)
{
	const uint32_t *src_bytes = (const uint32_t *)src;
	for (size_t i = 0; i < max_len; i++) {
		dest[i * 4] = src_bytes[i] & 0xFF;
		dest[i * 4 + 1] = (src_bytes[i] >> 8) & 0xFF;
		dest[i * 4 + 2] = (src_bytes[i] >> 16) & 0xFF;
		dest[i * 4 + 3] = (src_bytes[i] >> 24) & 0xFF;
	}	
}

inline void bytes_from_32bit_words_big_endian(uint8_t *dest, const void *src, size_t max_len)
{
    const uint32_t *src_bytes = (const uint32_t *)src;
	for (size_t i = 0; i < max_len; i++) {
        dest[i * 4]     = (src_bytes[i] >> 24) & 0xFF;
        dest[i * 4 + 1] = (src_bytes[i] >> 16) & 0xFF;
        dest[i * 4 + 2] = (src_bytes[i] >> 8)  & 0xFF;
        dest[i * 4 + 3] = src_bytes[i] & 0xFF;
    }   
}

void	print_hex(uint8_t *p, size_t hash_len) 
{
    size_t new_len = hash_len * 2 + 1;
	char hex_output[new_len];
	char hex_chars[] = "0123456789abcdef";

	for (size_t i = 0; i < hash_len; ++i) {
        hex_output[i * 2] = hex_chars[(p[i] >> 4) & 0xF];
        hex_output[i * 2 + 1] = hex_chars[p[i] & 0xF];
    }
    hex_output[hash_len * 2] = '\n';
    write(STDOUT_FILENO, hex_output, new_len);
}

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

void	print_str(const char *msg)
{
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}