#include "philo.h"

static int check_long(char *str)
{
    int sign;
    long ret;

    while (ft_isspace(*str))
        str++;
    sign = 1 - 2 * (*str == '-');
    str += (*str == '-' || *str == '+');
    if (!ft_isdigit(*str))
        return (false);
    ret = 0;
    while (ft_isdigit(*str))
    {
        if (sign == 1 && ((LONG_MAX - (*str - '0')) / 10 < ret))
            return (false);
        else if (sign == -1 && ((LONG_MIN + (*str - '0')) / 10 > -ret))
            return (false);
        ret = ret * 10 + (*str - '0');
        str++;
    }
    if (*str != '\0')
        return (false);
    return (true);
}

int check_input(int argc, char **argv)
{
    int index;

    index = 1;
    while (index < argc)
    {
        if (!check_long(argv[index]))
        {
            ft_fputs("Error: input is not a valid long\n", STDERR_FILENO);
            return (false);
        }
        index++;
    }
    return (true);
}
