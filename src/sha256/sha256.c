#include "sha256.h"

static const unsigned int hash_values[8]= { 0x6a09e667, 0xbb67ae85,
                    0x3c6ef372, 0xa54ff53a, 0x510e527f,
                    0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

static const unsigned int round_const[64] = {
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static const uint8_t padding[64] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void    sha256_init(sha256_ctx  *context)
{
    ft_memset(context, 0, sizeof(sha256_ctx));
    context->size = 0;
	context->state[0] = hash_values[0];
	context->state[1] = hash_values[1];
	context->state[2] = hash_values[2];
	context->state[3] = hash_values[3];
	context->state[4] = hash_values[4];
	context->state[5] = hash_values[5];
	context->state[6] = hash_values[6];
	context->state[7] = hash_values[7];
}

void    sha256_transform(uint32_t *state, uint32_t *input)
{   
    uint32_t s0;
    uint32_t s1;
    
    for (size_t i = 16; i < MAX_CHUNK_SIZE; i++)
    {
        s0 = ROTATE_RIGHT(input[i - 15], 7) XOR ROTATE_RIGHT(input[i - 15], 18) XOR SHIFT_RIGHT(input[i - 15], 3);
        s1 = ROTATE_RIGHT(input[i - 2], 17) XOR ROTATE_RIGHT(input[i - 2], 19) XOR SHIFT_RIGHT(input[i - 2], 10);
        input[i] = input[i - 16] + s0 + input[i - 7] + s1;
    }

    uint32_t a = state[0];
	uint32_t b = state[1];
	uint32_t c = state[2];
	uint32_t d = state[3];
	uint32_t e = state[4];
	uint32_t f = state[5];
	uint32_t g = state[6];
	uint32_t h = state[7];

    uint32_t tmp1, tmp2;
    for (size_t i = 0; i < MAX_CHUNK_SIZE; i++)
    {
        s1 = ROTATE_RIGHT(e, 6) XOR ROTATE_RIGHT(e, 11) XOR ROTATE_RIGHT(e, 25);
        tmp1 = h + s1 + CH(e, f ,g) + round_const[i] + input[i];
        s0 = ROTATE_RIGHT(a, 2) XOR ROTATE_RIGHT(a, 13) XOR ROTATE_RIGHT(a, 22);
        tmp2 = s0 + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + tmp1;
        d = c;
        c = b;
        b = a;
        a = tmp1 + tmp2;
    }
    state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	state[5] += f;
	state[6] += g;
	state[7] += h;
}

void    sha256_update(sha256_ctx *context, const uint8_t *input, size_t input_len)
{
    uint32_t        temp[64];
	unsigned int offset_idx = context->size % MAX_CHUNK_SIZE;
    context->size += (uint64_t)input_len;

	for (size_t i = 0; i < input_len; i++)
	{
		context->buffer[offset_idx++] = input[i];
		
		if (offset_idx % MAX_CHUNK_SIZE == 0)
		{
            bytes_to_32bit_words_big_endian(temp, context->buffer, MAX_CHUNK_SIZE / 4);
	        sha256_transform(context->state, temp);
			offset_idx = 0;
		}
	}
    
}

void sha256_update_padding(sha256_ctx *context)
{
    unsigned int offset_idx = context->size % MAX_CHUNK_SIZE;
	unsigned int padded_len = offset_idx < CHUNK_NO_PADDING ? CHUNK_NO_PADDING - offset_idx : (CHUNK_NO_PADDING + MAX_CHUNK_SIZE) - offset_idx;
	sha256_update(context, padding, padded_len);
	context->size -= (uint64_t)padded_len;
    uint32_t temp[64];
    bytes_to_32bit_words_big_endian(temp, context->buffer, (MAX_CHUNK_SIZE / 4) - 2);
    uint64_t size_bits = context->size * 8;
    temp[14] = (uint32_t)(size_bits >> 32);
    temp[15] = (uint32_t)size_bits;
    sha256_transform(context->state, temp);
}
// digest := hash := h0 append h1 append h2 append h3 append h4 append h5 append h6 append h7
void    sha256_final(sha256_ctx *context)
{
    sha256_update_padding(context);
    bytes_from_32bit_words_big_endian(context->digest, context->state, 8);
}

void    sha256_string(const uint8_t *input, size_t input_size, uint8_t *result)
{
    sha256_ctx  context;

    sha256_init(&context);
    sha256_update(&context, input, input_size);
    sha256_final(&context);
	ft_memcpy(result, context.digest, sizeof(context.digest));
}

void    sha256_file(int fd, uint8_t *result)
{
    sha256_ctx  context;
    char        buffer[MAX_READ_BUFFER_SIZE + 1];
    size_t      input_size = 0;

    sha256_init(&context);
    while((input_size = read(fd, buffer, MAX_READ_BUFFER_SIZE)) > 0){
        sha256_update(&context, (const uint8_t *)buffer, input_size);
    }
    sha256_final(&context);
	ft_memcpy(result, context.digest, sizeof(context.digest));
}