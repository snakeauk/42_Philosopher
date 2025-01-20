#include "philo.h"

void assign_forks(t_philo *philo, t_fork *forks, int index)
{
    int philo_nbr;

    philo_nbr = philo->table->philo_nbr;
    philo->right_fork = &forks[(index + 1) % philo_nbr];
    philo->left_fork = &forks[index];
    if (philo->id % 2 == 0)
    {
        philo->right_fork = &forks[index];
        philo->left_fork = &forks[(index + 1) % philo_nbr];
    }
}

void philo_init(t_table *table)
{
    int index;
    t_philo *philo;

    index = 0;
    while (index < table->philo_nbr)
    {
        philo = table->philos + index;
        philo->id = index + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->table = table;
        if (ft_mutex_init(&philo->mutex) != 0)
        {
            fprintf(stderr, "Error: mutex init failed for philo %d\n", philo->id);
            free_table(table);
            exit(EXIT_FAILURE);
        }
        assign_forks(philo, table->forks, index);
        index++;
    }
}

void init_data(t_table *table)
{
    int index;
    int status;

    table->end_simulation = false;
    table->all_threads_ready = false;
    table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
    if (!table->philos || !table->forks)
    {
        fprintf(stderr, "Error: memory allocation failed for philos or forks\n");
        free_table(table);
        exit(EXIT_FAILURE);
    }
    index = 0;
    while (index < table->philo_nbr)
    {
        status = ft_mutex_init(&table->forks[index].fork);
        if (status != 0)
        {
            fprintf(stderr, "Error: mutex init failed for fork %d\n", index);
            free_table(table);
            exit(EXIT_FAILURE);
        }
        table->forks[index].fork_id = index;
        index++;
    }
    ft_mutex_init(&table->table_mutex);
    philo_init(table);
}