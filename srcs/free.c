#include "philo.h"

void    free_table(t_table *table)
{
    if (table->forks)
        free(table->forks);
    if (table->philos)
        free(table->philos);
}
