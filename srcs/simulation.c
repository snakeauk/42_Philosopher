#include "philo.h"

void    philo_eat(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    pthread_mutex_lock(&philo->first_fork->fork);
    fork_pick(philo);
}

void    philo_rotine(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    while (table->simulation_continue)
    {
        if (philo->state == EATING)
            philo_eat(philo);
        else if (philo->state == SLEEPING)
            philo_sleep(philo);
        else if (philo->state == THINKING)
            philo_think(philo);
    }
}

void    philo_thread(t_table *table)
{
    int index;
    t_philo *philo;

    index = 0;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        if (pthread_create(&philo->thread_id, NULL, &philo_routine, philo))
            error_exit("Error: pthread_create failed", table);
        index++;
    }
}

int simulation(t_table *table)
{
    int index;
    t_philo *philo;

    philo_thread(table);
    index = 0;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        if (pthread_join(philo->thread_id, NULL))
            return (1);
        index++;
    }
    return (0);
}
