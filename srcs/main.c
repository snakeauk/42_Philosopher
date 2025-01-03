#include "philo.h"

// number_of_philosophers,
// time_to_die,
// time_to_eat,
// time_to_sleep,
// [number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv)
{
    t_philo *philo;

    if (argc != 5)
    {
        printf("Usage: ./philo <number_of_philosophers> ");
        printf("<time_to_die> <time_to_eat> <time_to_sleep>\n");
        return (1);
    }
    philo = init_philo(argc, argv);
    printf("OK\n");
    return (0);
}
