#include "ft_ssl.h"

static int open_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        print_error(file, strerror(errno));
    }
    return fd;
}

static void    print_options(t_ssl *data) {
    if (data->opt.quiet) {
        data->stdin_print_func = print_quiet;
        data->file_print_func = print_quiet;
        data->str_print_func = print_quiet;
        return ;
    }
    if (data->opt.append && data->opt.reverse) {
        data->stdin_print_func = print_append_str;
        data->file_print_func = print_file_reversed;
        data->str_print_func =  print_str_reversed;
        return ;
    }
    if (data->opt.append) {
        data->stdin_print_func = print_append_str;
        data->file_print_func = print_file;
        data->str_print_func =  print_append_str;
        return ;
    }
    if (data->opt.reverse) {
        data->stdin_print_func = print_stdin;
        data->file_print_func = print_file_reversed;
        data->str_print_func =  print_str_reversed;
        return ;
    }
    data->stdin_print_func = print_stdin;
    data->file_print_func = print_file;
    data->str_print_func =  print_append_str;

}

static void    exec_ssl(t_ssl *data)
{
    int hash_len = data->cmd == MD5 ? MD5 : SHA256;

    if (!data->file || data->opt.append) {
        data->stdin_input = data->file_func(STDIN_FILENO, data->result);
        if (data->stdin_input) {
            data->stdin_print_func(data->stdin_input, data->result, hash_len);
        }
    }
    if (data->str_input) {
        data->str_func((const uint8_t *)data->str_input, ft_strlen(data->str_input), data->result);
        data->str_print_func(data->str_input, data->result, hash_len);
    }
    for (size_t i = 0; data->file && data->file[i]; i++) {
        int fd = open_file(data->file[i]);
        if (fd == -1)
            continue;
        data->file_input = data->file_func(fd, data->result);
        data->file_print_func(data->file[i], data->result, hash_len);
    }
}

static void init_ssl(t_ssl *data) {
    switch (data->cmd) {
        case MD5:
            data->file_func = md5_file_func;
            data->str_func = md5_str_func;
            break;
        case SHA256:
            data->file_func = sha256_file_func;
            data->str_func = sha256_str_func;
            break;
        default:
            free(data);
            print_error("Error", USAGE_CMD_ERROR);
            exit(EXIT_FAILURE);
    }
}

void    ft_ssl(t_ssl *data) {
    init_ssl(data);
    print_options(data);
    exec_ssl(data);
}
