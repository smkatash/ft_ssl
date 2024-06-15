#include "md5.h"

static const unsigned int shifts_per_round[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 , \
						5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, \
						4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, \
						6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
static const unsigned int radians_const[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, \
						0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, \
						0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, \
						0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, \
						0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, \
						0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, \
						0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, \
						0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, \
						0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, \
						0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, \
						0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, \
						0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, \
						0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, \
						0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, \
						0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, \
						0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

/**
 * @brief MD5 initialization. 
 * Begins an MD5 operation, writing a new context
*/
static void	md5_init(md5_ctx *context)
{
	context->size = 0;
	context->state[0] = A_CONST;
	context->state[1] = B_CONST;
	context->state[2] = C_CONST;
	context->state[3] = D_CONST;
}

static void	md5_transform(uint32_t *state, uint32_t *input)
{
	uint32_t A = state[0];
	uint32_t B = state[1];
	uint32_t C = state[2];
	uint32_t D = state[3];
	uint32_t F;
	unsigned int j;

	for (unsigned int i = 0; i < 64; i++)
	{
		switch(ROUND(i))
		{
			case FIRST_ROUND:
				F = F(B, C, D);
				j = i;
				break;
			case SECOND_ROUND:
				F = G(B, C, D);
				j = (5 * i + 1) % 16;
				break;
			case THIRD_ROUND:
				F = H(B, C, D);
				j = (3 * i + 5) % 16;
				break;
			default:
				F = I(B, C, D);
				j = (7 * i) % 16;
				break;
		}
		F += A + radians_const[i] + input[j];
		A = D;
		D = C;
		C = B;
		B += ROTATE_LEFT(F, shifts_per_round[i]);
	}
	state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
}

/**
 * @brief MD5 block update operation. Continues an MD5 message-digest
 * operation, processing another message block, and updating the
 * context.
*/
static void	md5_update(md5_ctx *context, const uint8_t *input, size_t input_len)
{
	uint32_t        temp[16];
	unsigned int idx = context->size % 64;
    context->size += input_len;

	for (size_t i = 0; i < input_len; i++)
	{
		context->buffer[idx++] = (uint8_t)*(input + i);
		
		if (idx == 64)
		{
			bytes_to_32bit_words_little_endian(temp, (const void *)context->buffer, MAX_CHUNK_SIZE / 4);
			md5_transform(context->state, temp);
			idx = 0;
		}
	}
}

/** 
 * *  @brief message is "padded" so that its length (in bits) is
	congruent to 448, modulo 512.
	A single "1" bit is appended to the message, and then "0" bits are 
	appended.
	512 block - input len - 1 (for 1 bit)
	512 block = 448 + 64 bits (8 bytes input len)
	0x80 - the most significant bit
*/
static void md5_padding(const uint8_t *src, size_t src_len, uint8_t **dst, size_t *dst_len) {
    size_t new_len = src_len + 1;
    while (new_len % 64 != 56) {
        new_len++;
    }
    *dst = (uint8_t *)malloc(new_len + 8);
	if (!*dst)
    {
        // print error
        exit(1);
    }
    memcpy(*dst, src, src_len);
    (*dst)[src_len] = 0x80;
    for (size_t i = src_len + 1; i < new_len; i++) {
        (*dst)[i] = 0;
    }
    uint64_t src_len_bits = src_len * 8;
    memcpy(*dst + new_len, &src_len_bits, 8);
    *dst_len = new_len + 8;
}

static void	md5_final(md5_ctx *context)
{
	bytes_from_32bit_words_little_endian(context->digest, context->state, 4);
}

void    md5_string(const uint8_t *input, size_t input_size, uint8_t *result)
{
	md5_ctx	context;
	uint8_t	*padded_msg;
    size_t	padded_len;
	
	md5_init(&context);
    md5_padding(input, input_size, &padded_msg, &padded_len);
	size_t offset = 0;
    while (offset < padded_len) {
        size_t chunk_size = (padded_len - offset < MAX_CHUNK_SIZE) ? (padded_len - offset) : MAX_CHUNK_SIZE;
        md5_update(&context, &padded_msg[offset], chunk_size);
        offset += MAX_CHUNK_SIZE;
    }
	md5_final(&context);
	memcpy(result, context.digest, sizeof(context.digest));
	free(padded_msg);
}

void    md5_file(FILE *file, uint8_t *result)
{
	md5_ctx	context;
	char *buffer = malloc(1024);
    size_t input_size = 0;
	uint8_t	*padded_msg;
    size_t	padded_len;
	
	md5_init(&context);
	while((input_size = fread(buffer, 1, 1024, file)) > 0){
		md5_padding((const uint8_t*)buffer, input_size, &padded_msg, &padded_len);
		size_t offset = 0;
		while (offset < padded_len) {
			size_t chunk_size = (padded_len - offset < MAX_CHUNK_SIZE) ? (padded_len - offset) : MAX_CHUNK_SIZE;
			md5_update(&context, &padded_msg[offset], chunk_size);
			offset += MAX_CHUNK_SIZE;
		}
    }
	md5_final(&context);
	memcpy(result, context.digest, sizeof(context.digest));
	free(padded_msg);
	free(buffer);
}