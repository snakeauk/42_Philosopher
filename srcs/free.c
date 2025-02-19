#include "philo.h"

void	free_table(t_table *table)
{
	if (!table || !table->forks || !table->philos)
		return ;
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}
