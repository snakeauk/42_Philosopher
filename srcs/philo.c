#include "philo.h"

void    philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while ()
    {
        philo_think(philo);
        philo_eat(philo);
        philo_sleep(philo);
    }
}

void    philo_set(t_table *table)
{
    int index;
    t_philo *philo;

    index = 0;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        ft_mutex_init(&philo->philo_mutex);
        ft_thread_create(&philo->thread_id, philo_routine, philo);
        index++;
    }
}
