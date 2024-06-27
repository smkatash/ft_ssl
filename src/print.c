#include "ft_ssl.h"

void	print_hex(uint8_t *p, size_t hash_len) 
{
    size_t new_len = hash_len * 2;
	char hex_output[new_len];
	char hex_chars[] = "0123456789abcdef";

	for (size_t i = 0; i < hash_len; ++i) {
        hex_output[i * 2] = hex_chars[(p[i] >> 4) & 0xF];
        hex_output[i * 2 + 1] = hex_chars[p[i] & 0xF];
    }
    write(STDOUT_FILENO, hex_output, new_len);
}

void	print_error(const char *msg, const char* err)
{
	if (msg && err) {
        write(STDERR_FILENO, "ft_ssl: ", 9);
        write(STDERR_FILENO, msg, ft_strlen(msg));
        write(STDERR_FILENO, " : ", 4);
        write(STDERR_FILENO, err, ft_strlen(err));
        write(STDERR_FILENO, "\n", 2);
    }
}

void	print_str(const char *msg)
{
	if (msg) {
        write(STDOUT_FILENO, msg, ft_strlen(msg));
    }
}

void    print_quiet(const char* input, uint8_t *cksm, size_t cksm_len)
{
    (void)input;
    print_hex(cksm, cksm_len);
    print_str("\n");
}

void    print_stdin(const char* input, uint8_t *cksm, size_t cksm_len)
{
    (void)input;
    print_str(command_str(cksm_len));
    print_str("(stdin) = ");
    print_hex(cksm, cksm_len);
    print_str("\n");
}

void    print_append_str(const char* input, uint8_t *cksm, size_t cksm_len)
{
    print_str(command_str(cksm_len));
    print_str("(\"");
    print_str(input);
    print_str("\") = ");
    print_hex(cksm, cksm_len);
    print_str("\n");
}

void    print_file(const char* input, uint8_t *cksm, size_t cksm_len)
{
    print_str(command_str(cksm_len));
    print_str("(");
    print_str(input);
    print_str(") = ");
    print_hex(cksm, cksm_len);
    print_str("\n");
}

void    print_file_reversed(const char* input, uint8_t *cksm, size_t cksm_len)
{
    print_hex(cksm, cksm_len);
    print_str(" ");
    print_str(input);
    print_str("\n");
}

void    print_str_reversed(const char* input, uint8_t *cksm, size_t cksm_len)
{
    print_hex(cksm, cksm_len);
    print_str(" \"");
    print_str(input);
    print_str("\"");
    print_str("\n");
}
