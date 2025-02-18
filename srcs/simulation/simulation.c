#include "philo.h"

void	philo_set(t_table *table)
{
	int index;

	index = 0;
	while (index < table->philo_nbr)
	{
		ft_thread_create(&table->philos[index].thread, philo, &table->philos[index]);
		index++;
	}
}

void	monitor_set(t_table *table)
{
	ft_thread_create(&table->monitor.thread, monitor, table);
}

void	join_threads(t_table *table)
{
	int index;

	index = 0;
	while (index < table->philo_nbr)
	{
		ft_thread_join(table->philos[index].thread);
		index++;
	}
	ft_thread_join(table->monitor.thread);
}

void	simulation(t_table *table)
{
	monitor_set(table);
	philo_set(table);
	join_threads(table);
}