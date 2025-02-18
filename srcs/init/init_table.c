#include "philo.h"

void init_forks(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_nbr)
	{
		table->forks[index].id = index + 1;
		ft_mutex_init(&table->forks[index].fork);
		index++;
	}
}

static void	fork_set(t_philo *philo, t_table *table)
{
	t_fork	*tmp;
	t_fork	*forks;

	forks = table->forks;
	philo->first = &forks[philo->id - 1];
	if (philo->id == table->philo_nbr)
		philo->second = &forks[0];
	else
		philo->second = &forks[philo->id];
	if (philo->id % 2 == 0)
	{
		tmp = philo->first;
		philo->first = philo->second;
		philo->second = tmp;
	}
}

void	init_philo(t_table *table)
{
	int		index;
	t_philo	*philo;

	index = 0;
	while (index < table->philo_nbr)
	{
		philo = &table->philos[index];
		philo->id = index + 1;
		philo->status = THINKING;
		fork_set(philo, table);
		philo->meal_count = 0;
		philo->table = table;
		philo->is_full = false;
		philo->eat_last_time = 0;
		philo->is_set = false;
		ft_mutex_init(&philo->mutex);
		index++;
	}
}

int init_table(t_table *table)
{
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (EXIT_FAILURE);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		return (EXIT_FAILURE);
	init_forks(table);
	init_philo(table);
	ft_mutex_init(&table->print_mutex);
	ft_mutex_init(&table->monitor.mutex);
	table->monitor.is_stop = false;
	return (EXIT_SUCCESS);
}
