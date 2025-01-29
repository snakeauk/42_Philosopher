#include "philo.h"

void    error_exit(char *message, t_table *table)
{
    if (table)
        free_table(table);
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    t_table *table;
    if (argc < 5 || argc > 6)
    {
        printf("Usage: ./philo <number_of_philosophers> ");
        printf("<time_to_die> <time_to_eat> <time_to_sleep>");
        printf("[<number_of_times_each_philosopher_must_eat]\n");
        exit(EXIT_FAILURE);
    }
    table = init_table(argc, argv);
    if (!table)
        exit(EXIT_FAILURE);
    // printf("===============check_input: ===============\n");
    // printf("philo_nbr:%ld\ntime_to_die:%ld\ntime_to_eat:%ld\ntime_to_sleep:%ld\nnbr_limit_meals:%ld\n", table->philo_nbr, table->time_to_die, table->time_to_eat, table->time_to_sleep, table->nbr_limit_meals);
    simulation(table);
    free_table(table);
    return (0);
}
