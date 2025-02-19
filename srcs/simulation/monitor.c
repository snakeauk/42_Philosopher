#include "philo.h"

bool	is_continue(t_table *table, t_continue status)
{
	t_moniotor	*monitor;
	bool		is_stop;

	monitor = &table->monitor;
	ft_mutex_lock(&monitor->mutex);
	if (status == STOP)
		monitor->is_stop = true;
	is_stop = monitor->is_stop;
	ft_mutex_unlock(&monitor->mutex);
	if (is_stop == true)
		return (false);
	return (true);
}

void	dead_check(t_philo *philo)
{
	long	time;
	long	time_to_die;
	long	eat_last_time;
	
	time = get_time("ms");
	time_to_die = philo->table->time_to_die;
	ft_mutex_lock(&philo->mutex);
	eat_last_time = philo->eat_last_time;
	time = time - eat_last_time;
	if (philo->status != EATING && time > time_to_die)
	{
		philo->status = DEAD;
		philo_print(philo, "is died");
		is_continue(philo->table, STOP);
	}
	ft_mutex_unlock(&philo->mutex);
}

bool	full_check(t_table *table)
{
	int		index;
	t_philo	*philo;
	bool	is_all_full;

	index = 0;
	is_all_full = true;
	while (index < table->philo_nbr)
	{
		philo = &table->philos[index];
		ft_mutex_lock(&philo->mutex);
		if (philo->is_full == false)
			is_all_full = false;
		ft_mutex_unlock(&philo->mutex);
		index++;
	}
	return (is_all_full);
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		index;

	table = (t_table *)arg;
	ft_mutex_lock(&table->monitor.mutex);
	table->start_time = get_time("ms");
	table->is_set = true;
	ft_mutex_unlock(&table->monitor.mutex);
	simulation_start(table);
	while (is_continue(table, CONTINUE))
	{
		index = 0;
		while (index < table->philo_nbr)
		{
			dead_check(&table->philos[index]);
			index++;
		}
		if (full_check(table) == true)
			is_continue(table, STOP);
		usleep(100);
	}
	return (NULL);
}
