#include "debug.h"

void	debug_forks(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_nbr)
	{
		printf("philos[%d] = %d\n", index, table->philos[index].id);
		printf("\tright fork = %d\n", table->philos[index].first->id);
		printf("\tleft fork = %d\n", table->philos[index].second->id);
		index++;
	}
}
