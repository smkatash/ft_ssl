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

static const uint8_t padding[64] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/**
 * @brief MD5 initialization. 
 * Begins an MD5 operation, writing a new context
*/
static void	md5_init(md5_ctx *context)
{
	ft_memset(context, 0, sizeof(md5_ctx));
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
	uint32_t		temp[16];
	unsigned int offset_idx = context->size % MAX_CHUNK_SIZE;
    context->size += (uint64_t)input_len;

	for (size_t i = 0; i < input_len; i++)
	{
		context->buffer[offset_idx++] = input[i];
		
		if (offset_idx % MAX_CHUNK_SIZE == 0)
		{
			bytes_to_32bit_words_little_endian(temp, context->buffer, MAX_CHUNK_SIZE / 4);
			md5_transform(context->state, temp);
			offset_idx = 0;
		}
	}
}

static void	md5_update_padding(md5_ctx *context)
{
	unsigned int offset_idx = context->size % MAX_CHUNK_SIZE;
	unsigned int padded_len = offset_idx < CHUNK_NO_PADDING ? CHUNK_NO_PADDING - offset_idx : (CHUNK_NO_PADDING + MAX_CHUNK_SIZE) - offset_idx;
	md5_update(context, padding, padded_len);
	context->size -= (uint64_t)padded_len;
	uint32_t temp[16];
	bytes_to_32bit_words_little_endian(temp, context->buffer, (MAX_CHUNK_SIZE / 4) - 2);
	// append original length in bits mod 2^64
	uint64_t size_bits = context->size * 8;
	// lower and upper 32 bits
	temp[14] = (uint32_t)(size_bits);
    temp[15] = (uint32_t)(size_bits >> 32);
	md5_transform(context->state, temp);
}

static void	md5_final(md5_ctx *context)
{
	md5_update_padding(context);
	bytes_from_32bit_words_little_endian(context->digest, context->state, 4);
}

void    md5_string(const uint8_t *input, size_t input_size, uint8_t *result)
{
	md5_ctx	context;
	
	md5_init(&context);
    md5_update(&context, input, input_size);
	md5_final(&context);
	ft_memcpy(result, context.digest, sizeof(context.digest));
}

void    md5_file(int fd, uint8_t *result)
{
	md5_ctx	context;
	char	buffer[MAX_READ_BUFFER_SIZE + 1];
    size_t input_size = 0;
	
	md5_init(&context);
	while((input_size = read(fd, buffer, MAX_READ_BUFFER_SIZE)) > 0){
		md5_update(&context, (const uint8_t *)buffer, input_size);
    }
	md5_final(&context);
	ft_memcpy(result, context.digest, sizeof(context.digest));
}