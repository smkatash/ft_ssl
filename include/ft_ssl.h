#ifndef FT_SSL_H
#define FT_SSL_H

#include "md5.h"
#include "sha256.h"
#include "sha512.h"
#include <fcntl.h>
#include <string.h>

# define NUM_COMMANDS 3
# define NUM_PRINT_OPTIONS 5
# define MAX_FLAGS 4
# define USAGE_CMD_ERROR "invalid command.\
                    \nCommands:\
                    \n\tmd5 \n\tsha256\n\tsha512\
                    \nFlags:\
                    \n\t-p -q -r -s\n"
# define USAGE_ERROR "./ft_ssl command [flags] [file/string]\n"

# define command_token(cmd) (\
    ft_strcmp((cmd), "md5") == 0 ? MD5 : \
    ft_strcmp((cmd), "sha256") == 0 ? SHA256 : \
    ft_strcmp((cmd), "sha512") == 0 ? SHA512 : \
    0)
    
# define APPEND 1
# define QUIET 2
# define REVERSE 3
# define SUM 4
# define MD5 16
# define SHA256 32
# define SHA512 64
# define flags_token(cmd) (\
    ft_strcmp((cmd), "-p") == 0 ? APPEND : \
    ft_strcmp((cmd), "-q") == 0 ? QUIET : \
    ft_strcmp((cmd), "-r") == 0 ? REVERSE : \
    ft_strcmp((cmd), "-s") == 0 ? SUM  : \
    0)
# define command_str(cmd) (\
    cmd == MD5 ? "MD5" : \
    cmd == SHA256 ? "SHA-256" : \
    "SHA-512")

typedef struct {
	int	quiet;
	int	append;
	int	reverse;
	int	sum;
} options;

typedef struct s_ssl {
	options     opt;
	int         cmd;
	char        **file;
	char        *str_input;
	char        *file_input;
	char        *stdin_input;
    void        (*stdin_print_func)(const char* input, uint8_t *result, size_t len);
    void        (*file_print_func)(const char* input, uint8_t *result, size_t len);
    void        (*str_print_func)(const char* input, uint8_t *result, size_t len);
    char*       (*file_func)(int fd, uint8_t *result);
    void        (*str_func)(const uint8_t *input, size_t input_size, uint8_t *result);
    uint8_t     result[64];
} t_ssl;

typedef struct {
    int   cmd;
    char*(*file_func)(int fd, uint8_t *result);
    void (*str_func)(const uint8_t*, size_t, uint8_t*);
} ssl_command;

typedef struct {
    bool (*condition)(t_ssl *data);
    void (*stdin_print_func)();
    void (*file_print_func)();
    void (*str_print_func)();
} ssl_print_option;

static inline bool is_quiet(t_ssl *data) {
    return data->opt.quiet;
}

static inline bool is_quiet_and_append(t_ssl *data) {
    return data->opt.quiet && data->opt.append;
}

static inline bool is_append_and_reverse(t_ssl *data) {
    return data->opt.append && data->opt.reverse;
}

static inline bool is_append(t_ssl *data) {
    return data->opt.append;
}

static inline bool is_reverse(t_ssl *data) {
    return data->opt.reverse;
}

void    ft_ssl(t_ssl *data);
void	parse_input(char **argv, int argc, t_ssl *data);
void	free_data(t_ssl *data) ;
void	debug_data(t_ssl *data);
void	print_hex(uint8_t *p, size_t hash_len);
void	print_str(const char *msg);
void	print_error(const char *msg, const char *err);
void    print_quiet(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_append_str(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_file(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_file_reversed(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_stdin(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_str_reversed(const char* input, uint8_t *cksm, size_t cksm_len);
void    print_quiet_stdin(const char* input, uint8_t *cksm, size_t cksm_len);

#endif