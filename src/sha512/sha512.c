#include "sha512.h"

static const uint64_t hash_values[8] = { 0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 
                                            0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
                                            0x510e527fade682d1, 0x9b05688c2b3e6c1f, 
                                            0x1f83d9abfb41bd6b, 0x5be0cd19137e2179 };

static const uint64_t round_const[80] = { 0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 
                                0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 
                                0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 
                                0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
                                0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 
                                0x240ca1cc77ac9c65, 0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 
                                0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 
                                0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 
                                0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
                                0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 
                                0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 
                                0xc76c51a30654be30, 0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 
                                0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 
                                0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
                                0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 
                                0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 
                                0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 
                                0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 
                                0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
                                0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 
                                0x6c44198c4a475817 };

static const uint8_t padding[128] = { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void    sha512_init(sha512_ctx  *context)
{
    ft_memset(context, 0, sizeof(sha512_ctx));
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

void    sha512_transform(uint64_t *state, uint64_t *input)
{   
    uint64_t s0;
    uint64_t s1;

    for (size_t i = 16; i < 80; i++)
    {
        s0 = ROTATE_RIGHT_64(input[i - 15], 1) XOR ROTATE_RIGHT_64(input[i - 15], 8) XOR SHIFT_RIGHT(input[i - 15], 7);
        s1 = ROTATE_RIGHT_64(input[i - 2], 19) XOR ROTATE_RIGHT_64(input[i - 2], 61) XOR SHIFT_RIGHT(input[i - 2], 6);
        input[i] = input[i - 16] + s0 + input[i - 7] + s1;
    }

    uint64_t a = state[0];
	uint64_t b = state[1];
	uint64_t c = state[2];
	uint64_t d = state[3];
	uint64_t e = state[4];
	uint64_t f = state[5];
	uint64_t g = state[6];
	uint64_t h = state[7];

    uint64_t tmp1, tmp2;
    for (size_t i = 0; i < 80; i++)
    {
        s1 = ROTATE_RIGHT_64(e, 14) XOR ROTATE_RIGHT_64(e, 18) XOR ROTATE_RIGHT_64(e, 41);
        tmp1 = h + s1 + CH(e, f ,g) + round_const[i] + input[i];
        s0 = ROTATE_RIGHT_64(a, 28) XOR ROTATE_RIGHT_64(a, 34) XOR ROTATE_RIGHT_64(a, 39);
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

void    sha512_update(sha512_ctx *context, const uint8_t *input, size_t input_len)
{
    uint64_t        temp[80];
	unsigned int offset_idx = context->size % SHA512_CHUNK_SIZE;
    context->size += (uint64_t)input_len;

	for (size_t i = 0; i < input_len; i++)
	{
		context->buffer[offset_idx++] = input[i];
		
		if (offset_idx % SHA512_CHUNK_SIZE == 0)
		{
            bytes_to_64bit_words_big_endian(temp, context->buffer, SHA512_CHUNK_SIZE / 8);
	        sha512_transform(context->state, temp);
			offset_idx = 0;
		}
	}
}

void sha512_update_padding(sha512_ctx *context)
{
    unsigned int offset_idx = context->size % SHA512_CHUNK_SIZE;
	unsigned int padded_len = offset_idx < SHA512_CHUNK_NO_PADDING ? SHA512_CHUNK_NO_PADDING - offset_idx : (SHA512_CHUNK_NO_PADDING + SHA512_CHUNK_SIZE) - offset_idx;
	sha512_update(context, padding, padded_len);
	context->size -= (uint64_t)padded_len;
    uint64_t temp[80];
    bytes_to_64bit_words_big_endian(temp, context->buffer, (SHA512_CHUNK_SIZE / 8) - 2);
    uint64_t size_bits = context->size * 8;
    temp[14] = (uint64_t)(context->size >> 61);
    temp[15] = size_bits;
    sha512_transform(context->state, temp);
}

void    sha512_final(sha512_ctx *context)
{
    sha512_update_padding(context);
    bytes_from_64bit_words_big_endian(context->digest, context->state, 8);
}

void    sha512_str_func(const uint8_t *input, size_t input_size, uint8_t *result) {
    sha512_ctx  context;

    sha512_init(&context);
    sha512_update(&context, input, input_size);
    sha512_final(&context);
	ft_memcpy(result, context.digest, sizeof(context.digest));
}

char*   sha512_file_func(int fd, uint8_t *result) {
    sha512_ctx  context;
    char        buffer[MAX_READ_BUFFER_SIZE + 1];
    size_t      input_size = 0;
    size_t      total_read = 0; 
    char        *input = NULL;

    sha512_init(&context);
    while((input_size = read(fd, buffer, MAX_READ_BUFFER_SIZE)) > 0){
        sha512_update(&context, (const uint8_t *)buffer, input_size);
		if (fd == STDIN_FILENO && buffer[input_size - 1] == '\n')
			buffer[input_size - 1] = '\0';
		else 
			buffer[input_size] = '\0';
        input = ft_strjoin(input, buffer);
        total_read += input_size;
    }

    if (!input_size && !total_read) {
        input = ft_strdup("");
        sha512_update(&context, (const uint8_t *)input, input_size);
    } else if (input_size < 0) {
        print_error("read: ", strerror(errno));
        return (NULL);
    }
    sha512_final(&context);
	ft_memcpy(result, context.digest, sizeof(context.digest));
    return input;
}

