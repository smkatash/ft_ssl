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

void    sha256_init(sha256_ctx  *context)
{
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

static void sha256_padding(const uint8_t *src, size_t src_len, uint8_t **dst, size_t *dst_len) {
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
    to_big_endian(*dst + new_len, &src_len_bits, sizeof(src_len_bits));
    *dst_len = new_len + 8;
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
    context->size += input_len;
    
	bytes_to_32bit_words_big_endian(temp, input, MAX_CHUNK_SIZE / 4);
	sha256_transform(context->state, temp);
}
// digest := hash := h0 append h1 append h2 append h3 append h4 append h5 append h6 append h7
void    sha256_final(sha256_ctx *context)
{
    bytes_from_32bit_words_big_endian(context->digest, context->state, 8);
}

void    sha256(const uint8_t *input, size_t input_size, uint8_t *result)
{
    sha256_ctx  context;
    uint8_t     *padded_msg;
    size_t      padded_len;
    size_t      offset = 0;
    size_t      chunk_size = 0;

    sha256_init(&context);
    sha256_padding(input, input_size, &padded_msg, &padded_len);
    while (offset < padded_len) {
        chunk_size = (padded_len - offset < MAX_CHUNK_SIZE) ? (padded_len - offset) : MAX_CHUNK_SIZE;
        sha256_update(&context, &padded_msg[offset], chunk_size);
        offset += MAX_CHUNK_SIZE;
    }
    sha256_final(&context);
	memcpy(result, context.digest, sizeof(context.digest));
    free(padded_msg);
}