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
        ft_thread_join(table->philos[index].thread_id);
        index++;
    }
    ft_thread_join(table->monitor.thread_id);
}

void    simulation(t_table *table)
{
    simulation_set(table);
    simulation_wait(table);
}
