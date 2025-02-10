#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;

    if (argc < 5 || argc > 6 || !check_input(argc, argv))
    {
        printf("Usage: ./philo <number_of_philosophers> ");
        printf("<time_to_die> <time_to_eat> <time_to_sleep>");
        printf("[<number_of_times_each_philosopher_must_eat]\n");
        exit(EXIT_FAILURE);
    }
    if (init_arg(&table, argv) != EXIT_SUCCESS)
        return (EXIT_FAILURE);
    init_table(&table);
    simulation(&table);
    free_table(&table);
    return (0);
}
