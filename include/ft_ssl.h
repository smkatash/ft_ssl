#ifndef FT_SSL_H
#define FT_SSL_H

#include "md5.h"

# define MAX_FLAGS 4
# define command_token(cmd) (\
    strcmp((cmd), "md5") == 0 ? MD5 : \
    strcmp((cmd), "sha256") == 0 ? SHA256 : \
    0)
# define APPEND 1
# define QUIET 2
# define REVERSE 3
# define SUM 4
# define MD5 5
# define SHA256 6
# define flags_token(cmd) (\
    strcmp((cmd), "-p") == 0 ? APPEND : \
    strcmp((cmd), "-q") == 0 ? QUIET : \
    strcmp((cmd), "-r") == 0? REVERSE : \
    strcmp((cmd), "-s") == 0 ? SUM  : \
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
	char        *input;
    uint8_t     result[16];
} t_ssl;

void	parse_input(char **argv, int argc, t_ssl *data);
void	debug_data(t_ssl *data);

#endif