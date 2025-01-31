#include "philo.h"

void free_fork (t_fork *fork)
{
    if (fork)
        free(fork);
}

void free_philo(t_philo *philo)
{
    if (philo)
    {
        if (philo->first_fork)
            free_fork(philo->first_fork);
        if (philo->second_fork)
            free_fork(philo->second_fork);
        free(philo);
    }
}


void    free_table(t_table *table)
{
    if (table->forks)
        free(table->forks);
    if (table->philos)
        free(table->philos);
    if (table)
        free(table);
}
