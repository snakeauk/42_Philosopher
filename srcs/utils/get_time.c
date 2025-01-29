#include "utils.h"

long    get_time(char *timecode)
{
    struct timeval tv;
    
    if (gettimeofday(&tv, NULL))
    {
        ft_fputs("Error: gettimeofday faild", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    if (ft_strcmp(timecode, "s") == 0)
        return (tv.tv_sec + (tv.tv_usec / 1000000));
    else if (ft_strcmp(timecode, "ms") == 0)
        return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    else if (ft_strcmp(timecode, "us") == 0)
        return ((tv.tv_sec * 1000000) + tv.tv_usec);
    else
        ft_fputs("Error: get_time: invalid argment\n", STDERR_FILENO);
    return (-1);
}
// int main(int argc, char **argv)
// {
//     long    time;
//     if (argc != 2)
//     {
//         printf("Usage: invalid argmeant\n");
//         return (EXIT_FAILURE);
//     }
//     while (1)
//     {
//         time = get_time(argv[1]);
//         printf("time: %ld\n", time);
//         usleep(10000000);
//     }
//     return (EXIT_SUCCESS);
// }