#include "philo.h"

void    error_exit(char *message, t_table *table)
{
    if (table)
        free_table(table);
    error_message(message);
    exit(EXIT_FAILURE);
}

int error_message(char *message)
{
    return (ft_fputs(message, STDERR_FILENO));
}
