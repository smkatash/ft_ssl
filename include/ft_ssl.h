#ifndef FT_SSL_H
#define FT_SSL_H

#include "md5.h"
#include "sha256.h"
#include <fcntl.h>

# define MAX_FLAGS 4
# define command_token(cmd) (\
    ft_strcmp((cmd), "md5") == 0 ? MD5 : \
    ft_strcmp((cmd), "sha256") == 0 ? SHA256 : \
    0)
# define APPEND 1
# define QUIET 2
# define REVERSE 3
# define SUM 4
# define MD5 16
# define SHA256 32
# define flags_token(cmd) (\
    ft_strcmp((cmd), "-p") == 0 ? APPEND : \
    ft_strcmp((cmd), "-q") == 0 ? QUIET : \
    ft_strcmp((cmd), "-r") == 0 ? REVERSE : \
    ft_strcmp((cmd), "-s") == 0 ? SUM  : \
    0)

typedef struct {
	int	quiet;
	int	append;
	int	reverse;
	int	sum;
} options;

typedef struct s_ssl {
	options     opt;
	int         cmd;
	char        *file;
	char        *input;
    uint8_t     md5_result[16];
    uint8_t     sha256_result[32];
} t_ssl;

void	parse_input(char **argv, int argc, t_ssl *data);
void	debug_data(t_ssl *data);

#endif