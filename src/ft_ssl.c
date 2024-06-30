#include "ft_ssl.h"

static const ssl_command commands[] = {
    {MD5, md5_file_func, md5_str_func},
    {SHA256, sha256_file_func, sha256_str_func},
    {SHA512, sha512_file_func, sha512_str_func}
};

static const ssl_print_option print_options[] = {
        { is_quiet_and_append, print_quiet_stdin, print_quiet, print_quiet },
        { is_quiet, print_quiet, print_quiet, print_quiet },
        { is_append_and_reverse, print_append_str, print_file_reversed, print_str_reversed },
        { is_append, print_append_str, print_file, print_append_str },
        { is_reverse, print_stdin, print_file_reversed, print_str_reversed }
};

static int open_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        print_error(file, strerror(errno));
    }
    return fd;
}

static void    exec_ssl(t_ssl *data)
{
    int hash_len = data->cmd;

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

static void    set_print_options(t_ssl *data) {
    for (int i = 0; i < NUM_PRINT_OPTIONS; i++) {
        if (print_options[i].condition(data)) {
            data->stdin_print_func = print_options[i].stdin_print_func;
            data->file_print_func = print_options[i].file_print_func;
            data->str_print_func = print_options[i].str_print_func;
            return;
        }
    }
    data->stdin_print_func = print_stdin;
    data->file_print_func = print_file;
    data->str_print_func = print_append_str;
}

static void init_ssl(t_ssl *data) {
    for (size_t i = 0; i < NUM_COMMANDS; i++) {
        if (commands[i].cmd == data->cmd) {
            data->file_func = commands[i].file_func;
            data->str_func = commands[i].str_func;
            return;
        }
    }
    free(data);
    print_error("Error", USAGE_CMD_ERROR);
    exit(EXIT_FAILURE);
}

void    ft_ssl(t_ssl *data) {
    init_ssl(data);
    set_print_options(data);
    exec_ssl(data);
}
