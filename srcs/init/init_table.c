#include "philo.h"

void init_forks(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_nbr)
    {
        table->forks[index].id = index + 1;
        ft_mutex_init(&table->forks[index].fork);
        index++;
    }
}

void init_philo(t_table *table)
{
    int index;
    t_philo *philo;

    index = 0;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        philo->id = index + 1;
        philo->last_eat = 0;
        philo->left = &table->forks[index];
        if (philo->id == table->philo_nbr)
            philo->right = &table->forks[0];
        else
            philo->right = &table->forks[index + 1];
        philo->meal_count = 0;
        philo->table = table;
        index++;
    }
}

int init_table(t_table *table)
{
    table->stop = 0;
    table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
    if (!table->philos)
        return (EXIT_FAILURE);
    table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
    if (!table->forks)
        return (EXIT_FAILURE);
    init_forks(table);
    init_philo(table);
    ft_mutex_init(&table->print_mutex);
    ft_mutex_init(&table->m_stop);
    ft_mutex_init(&table->m_eat);
    ft_mutex_init(&table->continue_mutex);
    return (EXIT_SUCCESS);
}
