#include "utils.h"

size_t  ft_strlen(const char *s)
{
    size_t  count;

    count = 0;
    while(*s)
    {
        count++;
        s++;
    }
    return (count);
}
// #include <string.h>
// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         printf("Error: invalid argment\n");
//         return (EXIT_FAILURE);
//     }
//     printf("===%s %s===\n", argv[0], argv[1]);
//     printf("   strlen: %lu\n", strlen(argv[1]));
//     printf("ft_strlen: %lu\n", ft_strlen(argv[1]));
//     return(EXIT_SUCCESS);
// }