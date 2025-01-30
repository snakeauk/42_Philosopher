#include "philo.h"

void    error_exit(char *message, t_table *table)
{
    if (table)
        free_table(table);
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

int error_message(char *message)
{
    return (ft_fputs("%s\n", STDERR_FILENO));
}

int main(int argc, char **argv)
{
    t_table *table;

    if (argc < 5 || argc > 6 || check_input(argc, argv))
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
    if (init_table(argc, argv) != EXIT_SUCCESS)
        return (EXIT_FAILURE);
    init_mutex(table);
    simulation(table);
    free_table(table);
    return (0);
}
