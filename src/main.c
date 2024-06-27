#include "ft_ssl.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        print_error("usage", USAGE_ERROR);
        return (EXIT_FAILURE);
    }
    t_ssl data;
    ft_memset(&data, 0, sizeof(data));
    parse_input(argv, argc, &data);
    // TODO clean up and test more
    //debug_data(&data);
    ft_ssl(&data);
    free_data(&data);
    // TODO check with valgrind
    system("leaks ft_ssl");
    return (EXIT_SUCCESS);
}