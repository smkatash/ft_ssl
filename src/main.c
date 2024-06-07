#include "ft_ssl.h"

void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
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
    if(data.cmd == MD5 && data.input)
    {
        md5((const uint8_t *)data.input, strlen(data.input), data.result);
        print_hash(data.result);
    }
}