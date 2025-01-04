#include "philo.h"

int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int is_number(char *num)
{
    if (!num)
        return (0);
    while (*num)
    {
        if (!ft_isdigit(*num))
            return (0)
        num++;
    }
    return (1);
}

int is_uinteger(char *num)
{
    int n;
    if (!num)
        return (0);
    if (!is_number(num))
        return (0);
    n = 0;
    while (*num)
    {

        num++;
    }
}

t_philo *init_philo(int argc, char **argv)
{
    t_philo *philo;
    int     index;

    index = 0;
    while (index < argc)
    {
        is_int(argv[index]);
        index++;
    }
}

