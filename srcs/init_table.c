#include "philo.h"

void set_forks(t_philo *philo, t_fork *forks, int index)
{
    int philo_nbr;

    philo_nbr = philo->table->philo_nbr;
    if (index % 2 == 0)
    {
        philo->first_fork = &forks[index];
        philo->second_fork = &forks[(index + 1) % philo_nbr];
    }
    else
    {
        philo->first_fork = &forks[(index + 1) % philo_nbr];
        philo->second_fork = &forks[index];
    }
}

void    init_philo(t_table *table)
{
    int index;
    t_philo *philo;

    if (!table)
        error_exit("Error: table is NULL", table);
    index = 0;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        philo->id = index + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->table = table;
        set_forks(philo, table->forks, index);
        if (philo->id % 2 == 0)
            philo->state = THINKING;
        else
            philo->state = EATING;
        index++;
    }
}

void    init_forks(t_table *table)
{
    int index;

    if (!table)
        error_exit("Error: table is NULL", table);
    index = 0;
    while (index < table->philo_nbr)
    {
        table->forks[index].fork_id = index;
        index++;
    }
}

void    init_env(t_table *table)
{
    table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
    if (!table->philos || !table->forks)
        error_exit("Error: malloc failed", table);
    init_forks(table);
    init_philo(table);
}

static  void    init_table_value(t_table *table, char **argv)
{
    table->philo_nbr = ft_atol(argv[1]);
    table->time_to_die = ft_atol(argv[2]) * 1000;
    table->time_to_eat = ft_atol(argv[3]) * 1000;
    table->time_to_sleep = ft_atol(argv[4]) * 1000;
    if (argv[5])
        table->nbr_limit_meals = ft_atol(argv[5]);
    else
        table->nbr_limit_meals = -1;
    if (table->philo_nbr < 1)
        error_exit("Error: number of philosophers must be at least 1", table);
    if (table->time_to_die < 60 || table->time_to_eat < 60 || table->time_to_sleep < 60)
        error_exit("Error: times must be greater than 60ms", table);
}

t_table *init_table(int argc, char **argv)
{
    t_table *table;

    if (!check_input(argc, argv))
        return (NULL);
    table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        exit(EXIT_FAILURE);
    init_table_value(table, argv);
    init_env(table);
    return (table);
}
