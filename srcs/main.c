#include "philo.h"

void    error_exit(char *message, t_table *table)
{
    if (table)
        free_table(table);
    error_message(message);
    exit(EXIT_FAILURE);
}

int error_message(char *message)
{
    return (ft_fputs(message, STDERR_FILENO));
}

int init_mutex(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_nbr)
    {
        ft_mutex_init(&table->philos[index].philo_mutex);
        ft_mutex_init(&table->philos[index].philo_mutex);
        index++;
    }
    ft_mutex_init(&table->monitor.monitor_mutex);
    return (EXIT_SUCCESS);
}

void mutex_destroy(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->philos[index].philo_mutex);
        pthread_mutex_destroy(&table->philos[index].philo_mutex);
        index++;
    }
    pthread_mutex_destroy(&table->monitor.monitor_mutex);
}

int main(int argc, char **argv)
{
    t_table *table;

    if (argc < 5 || argc > 6 || !check_input(argc, argv))
    {
        printf("Usage: ./philo <number_of_philosophers> ");
        printf("<time_to_die> <time_to_eat> <time_to_sleep>");
        printf("[<number_of_times_each_philosopher_must_eat]\n");
        exit(EXIT_FAILURE);
    }
    table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        exit(EXIT_FAILURE);
    if (init_arg(table, argv) != EXIT_SUCCESS)
        return (EXIT_FAILURE);
    // printf("%ld\n", table->philo_nbr);
    init_table(table);
    init_mutex(table);
    simulation(table);
    mutex_destroy(table);
    free_table(table);
    return (0);
}
