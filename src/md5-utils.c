#include "md5.h"

void	bytes_to_32bit_words(uint32_t *dest, uint8_t *src, size_t max_len)
{
	for (size_t j = 0; j < max_len; j++)
	{
		// fill up dest from src, each iter 4 bytes int0 32-bit words
		dest[j] = (uint32_t)(src[(j * 4) + 3]) << 24 |
			(uint32_t)(src[(j * 4) + 2]) << 16 |
			(uint32_t)(src[(j * 4) + 1]) <<  8 |
			(uint32_t)(src[(j * 4)]);
	}	
}

void	bytes_from_32bit_words(uint8_t *dest, uint32_t *src, size_t max_len)
{
	for (size_t i = 0; i < max_len; i++) {
		dest[i * 4] = (uint8_t)(src[i] & 0xFF);
		dest[i * 4 + 1] = (uint8_t)((src[i] >> 8) & 0xFF);
		dest[i * 4 + 2] = (uint8_t)((src[i] >> 16) & 0xFF);
		dest[i * 4 + 3] = (uint8_t)((src[i] >> 24) & 0xFF);
	}	
}

void    print_bits(const uint8_t *msg, size_t len) 
{
	for (size_t i = 0; i < len; i++) {
		for (int j = 7; j >= 0; j--) {
			putchar((msg[i] & (1 << j)) ? '1' : '0');
		}
		putchar(' ');
		if ((i + 1) % 8 == 0) {
			putchar('\n');
		}
	}
	printf("\n");
}