#include "philo.h"

int    init_arg(t_table *table, char **argv)
{
    int status;

    status = EXIT_SUCCESS;
    table->philo_nbr = ft_atol(argv[1]);
    if (table->philo_nbr < 1 || table->philo_nbr > 200)
    {
        error_exit("Error: invalid number of philosophers", table);
        status = EXIT_FAILURE;
    }
    table->time_to_die = ft_atol(argv[2]);
    table->time_to_eat = ft_atol(argv[3]);
    table->time_to_sleep = ft_atol(argv[4]);
    if (argv[5])
        table->limit_meals = ft_atol(argv[5]);
    else
        table->limit_meals = -1;
    if (table->time_to_die < 60 || table->time_to_eat < 60 || table->time_to_sleep < 60 || (argv[5] && table->limit_meals < 1))
    {
        error_exit("Error: times must be greater than 60ms", table);
        status = EXIT_FAILURE;
    }
    if (status == EXIT_FAILURE)
        free(table);
    return (status);
}
