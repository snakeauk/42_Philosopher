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

    eat_time = 0;
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
        eat_time = table->time_to_eat;
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
    t_philo *philo;

    index = 0;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        philo->id = index + 1;
        philo->meals_counter = 0;
        philo->last_meal_time = 0;
        philo->last_sleep_time = 0;
        philo->next_eat_time = set_eat_time(philo);
        philo->state = SLEEPING;
        philo->is_set = false;
        philo->table = table;
        if (index == 0)
        {
            philo->first_fork = &table->forks[table->philo_nbr - 1];
            philo->second_fork = &table->forks[index];
        }
        else
        {
            philo->first_fork = &table->forks[index - 1];
            philo->second_fork = &table->forks[index];
        }
        index++;
    }
}

void init_table(t_table *table)
{
    table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
    table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
    if (!table->forks || !table->philos)
        error_exit("Error: malloc failed", table);
    table->interval = init_interval(table);
    init_philo_values(table);
    init_forks(table);
}
