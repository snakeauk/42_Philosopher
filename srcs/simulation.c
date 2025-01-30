#include "philo.h"

void    simulation_set(t_table *table)
{
    philo_set(table);
    monitor_set(table);
}

void    simulation_wait(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->philos[index].philo_mutex);
        pthread_mutex_destroy(&table->forks[index].fork);
        index++;
    }
    pthread_mutex_destroy(&table->monitor.monitor_mutex);
}

void    simulation(t_table *table)
{
    simulation_set(table);
    simulation_wait(table);
}
