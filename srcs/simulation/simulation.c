#include "philo.h"

void    simulation_wait(t_table *table)
{
    int index;

    index = 0;
    ft_thread_join(table->monitor.monitor_thread);
    while (index < table->philo_nbr)
    {
        ft_thread_join(table->philos[index].thread);
        index++;
    }
}

void destroy_mutex(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->philos[index].mutex);
        pthread_mutex_destroy(&table->forks[index].fork);
        index++;
    }
    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->m_stop);
    pthread_mutex_destroy(&table->m_eat);
    pthread_mutex_destroy(&table->continue_mutex);
}

void    monitor_create(t_table *table)
{
    ft_thread_create(&table->monitor.monitor_thread, check_dead, table);
}

void    simulation(t_table *table)
{
    monitor_create(table);
    philo_set(table);
    simulation_wait(table);
    destroy_mutex(table);
}
