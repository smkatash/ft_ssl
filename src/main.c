#include "ft_ssl.h"

int    md5_input(t_ssl *data)
{
    if (data->input && ft_strlen(data->input) > 0) {
        md5_string((const uint8_t *)data->input, ft_strlen(data->input), data->md5_result);
    } else {
        md5_file(STDIN_FILENO, data->md5_result);
    }
    print_hex(data->md5_result, MD5);
    return (EXIT_SUCCESS);
}

int    sha256_input(t_ssl *data)
{
    if (data->input && ft_strlen(data->input) > 0) {
        sha256_string((const uint8_t *)data->input, ft_strlen(data->input), data->sha256_result);
    } else {
        sha256_file(STDIN_FILENO, data->sha256_result);
    }
    print_hex(data->sha256_result, SHA256);
    return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    int ret = 0;
    if (argc < 2)
    {
        return (EXIT_FAILURE);
    }
    t_ssl data;
    ft_memset(&data, 0, sizeof(data));
    parse_input(argv, argc, &data);
    debug_data(&data);
    if(data.cmd == MD5)
    {
       ret = md5_input(&data);
    } else {
        ret = sha256_input(&data);
    }
    return (ret);
}