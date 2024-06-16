#include "ft_ssl.h"

void print_hash(uint8_t *p, size_t hash_len){
    for(unsigned int i = 0; i < hash_len; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
}

void    md5_input(t_ssl *data)
{
    if (data->input && strlen(data->input) > 0) {
        md5_string((const uint8_t *)data->input, strlen(data->input), data->md5_result);
    } else {
        md5_file(STDIN_FILENO, data->md5_result);
    }
    print_hash(data->md5_result, MD5);
}

void    sha256_input(t_ssl *data)
{
    if (data->input && strlen(data->input) > 0) {
        sha256_string((const uint8_t *)data->input, strlen(data->input), data->sha256_result);
    } else {
        sha256_file(STDIN_FILENO, data->sha256_result);
    }
    print_hash(data->sha256_result, SHA256);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        exit(1);
    }
    t_ssl data;
    memset(&data, 0, sizeof(data));
    parse_input(argv, argc, &data);
    debug_data(&data);
    if(data.cmd == MD5)
    {
       md5_input(&data);
    } else {
        sha256_input(&data);
    }
    printf("Exiting\n");
    return (0);
}