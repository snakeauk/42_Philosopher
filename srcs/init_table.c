#include "philo.h"

long    init_interval(t_table *table)
{
    long interval;
    long philo_nbr;
    long time_to_eat;
    long time_to_sleep;
    
    philo_nbr = table->philo_nbr;
    time_to_eat = table->time_to_eat;
    time_to_sleep = table->time_to_sleep;
    if ((philo_nbr / 2) == 0)
        return (time_to_eat + time_to_sleep);
    interval = time_to_eat * 2;
    if (interval < time_to_eat + time_to_sleep)
        return (time_to_eat + time_to_sleep);
    return (interval);
}

long    set_eat_time(t_philo *philo)
{
    t_table *table;
    long    eat_time;

    table = philo->table;
    if (table->philo_nbr % 2 == 0)
    {
        if (philo->id % 2 == 0)
            eat_time = table->time_to_eat;
        else
            eat_time = 0;
    }
    else
    {
        
    }
    return (eat_time);
}

void    init_forks(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_nbr)
    {
        table->forks[index].fork_id = index;
        ft_mutex_init(&table->forks[index].fork);
        index++;
    }
}

void    init_philo_values(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_nbr)
    {
        table->philos[index].id = index + 1;
        table->philos[index].meals_counter = 0;
        table->philos[index].last_meal_time = 0;
        table->philos[index].last_sleep_time = 0;
        table->philos[index].next_eat_time = set_eat_time(&table->philos[index]);
        table->philos[index].state = SLEEPING;
        table->philos[index].table = table;
        if (index == 0)
        {
            table->philos[index].first_fork = &table->forks[table->philo_nbr - 1];
            table->philos[index].second_fork = &table->forks[index];
        }
        else
        {
            table->philos[index].first_fork = &table->forks[index - 1];
            table->philos[index].second_fork = &table->forks[index];
        }
        index++;
    }
}

int *init_table(t_table *table)
{
    table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
    table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
    if (!table->forks || !table->philos)
        error_exit("Error: malloc failed", table);
    table->interval = init_interval(table);
    init_philo_values(table);
    init_forks(table);
    init_philo(table);
    return (EXIT_SUCCESS);
}
