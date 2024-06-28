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

inline void	bytes_to_64bit_words_big_endian(uint64_t *dest, const void *src, size_t max_len)
{
	const uint8_t *src_bytes = (const uint8_t *)src;
	for (size_t j = 0; j < max_len; j++) {
		dest[j] = ((uint64_t)src_bytes[8 * j ] << 56) |
                    ((uint64_t)src_bytes[8 * j +1] << 48) |
                    ((uint64_t)src_bytes[8 * j +2] << 40) |
                    ((uint64_t)src_bytes[8 * j +3] << 32) |
                    ((uint64_t)src_bytes[8 * j +4] << 24) |
                    ((uint64_t)src_bytes[8 * j +5] << 16) |
                    ((uint64_t)src_bytes[8 * j +6] << 8) |
                    ((uint64_t)src_bytes[8 * j +7]);
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

inline void bytes_from_64bit_words_big_endian(uint8_t *output, const uint64_t *src, size_t len) {
	const uint64_t *src_bytes = (const uint64_t *)src;
    for (size_t i = 0; i < len; i++) {
        output[8 * i] = (uint8_t)(src_bytes[i] >> 56);
        output[8 * i + 1] = (uint8_t)(src_bytes[i] >> 48);
        output[8 * i + 2] = (uint8_t)(src_bytes[i] >> 40);
        output[8 * i + 3] = (uint8_t)(src_bytes[i] >> 32);
        output[8 * i + 4] = (uint8_t)(src_bytes[i] >> 24);
        output[8 * i + 5] = (uint8_t)(src_bytes[i] >> 16);
        output[8 * i + 6] = (uint8_t)(src_bytes[i] >> 8);
        output[8 * i + 7] = (uint8_t)src_bytes[i];
    }
}
