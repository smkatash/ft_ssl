#include "libft.h"

size_t arr_len(char** arr) {
    size_t len = 0;
    if (!arr) {
        return len;
    }
    while (arr[len]) {
        len++;
    }
    return len;
}

char **ft_append_array(const char* str, char** arr) {
    char **tmp_arr = NULL;
    size_t len = arr_len(arr);
    if (!arr) {
        tmp_arr = malloc((len + 2) * sizeof(char*));
        tmp_arr[0] = ft_strdup(str);
        tmp_arr[1] = NULL;
    } else {
        tmp_arr = realloc(arr, (len + 2) * sizeof(char*));
        tmp_arr[len] = ft_strdup(str);
        tmp_arr[len + 1] = NULL;
    }
    return (tmp_arr);
}
