#include "philo.h"

void    free_table(t_table *table)
{
    if (table->philos)
        free(table->philos);
    if (table)
        free(table);
}
