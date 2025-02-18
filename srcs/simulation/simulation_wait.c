#include "philo.h"

static void	simulation_philo_start(t_table *table)
{
	int index;
	t_philo *philo;
	bool is_wait;

	while (1)
	{
		is_wait = true;
		index = 0;
		while (index < table->philo_nbr)
		{
			philo = &table->philos[index];
			ft_mutex_lock(&philo->mutex);
			if (philo->is_set == false)
				is_wait = false;
			ft_mutex_unlock(&philo->mutex);
			index++;
		}
		if (is_wait)
			break ;
	}
}

static void	simulation_monitor_start(t_table *table)
{
	bool is_wait;

	while (1)
	{
		is_wait = true;
		ft_mutex_lock(&table->monitor.mutex);
		if (table->is_set == false)
			is_wait = false;
		ft_mutex_unlock(&table->monitor.mutex);
		if (is_wait)
			break ;
	}
}

void	simulation_start(t_table *table)
{
	simulation_philo_start(table);
	simulation_monitor_start(table);
}
