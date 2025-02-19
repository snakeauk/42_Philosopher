#include "philo.h"

void philo_print(t_philo *philo, char *message)
{
	long	time;
	bool	is_stop;

	ft_mutex_lock(&philo->table->monitor.mutex);
	is_stop = philo->table->monitor.is_stop;
	ft_mutex_unlock(&philo->table->monitor.mutex);
	ft_mutex_lock(&philo->table->print_mutex);
	time = get_time("ms") - philo->table->start_time;
	if (!is_stop)
		printf("%ld %d %s\n", time, philo->id, message);
	ft_mutex_unlock(&philo->table->print_mutex);
}

void	philo_eat(t_philo *philo)
{
	ft_mutex_lock(&philo->first->fork);
	philo_print(philo, "has taken a fork");
	if (philo->table->philo_nbr == 1)
	{
		ft_mutex_lock(&philo->mutex);
		philo->status = DEAD;
		ft_mutex_unlock(&philo->mutex);
		ft_usleep(philo->table->time_to_die);
		ft_mutex_unlock(&philo->first->fork);
		return ;
	}
	ft_mutex_lock(&philo->second->fork);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	ft_mutex_lock(&philo->mutex);
	philo->status = EATING;
	philo->eat_last_time = get_time("ms");
	philo->meal_count++;
	if (philo->meal_count == philo->table->limit_meals)
		philo->is_full = true;
	ft_mutex_unlock(&philo->mutex);
	ft_usleep(philo->table->time_to_eat);
	ft_mutex_unlock(&philo->first->fork);
	ft_mutex_unlock(&philo->second->fork);
}

void	philo_sleep(t_philo *philo)
{
	ft_mutex_lock(&philo->mutex);
	philo->status = SLEEPING;
	ft_mutex_unlock(&philo->mutex);
	philo_print(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	ft_mutex_lock(&philo->mutex);
	philo->status = THINKING;
	ft_mutex_unlock(&philo->mutex);
	philo_print(philo, "is thinking");
}

void	*philo(void *arg)
{
	t_philo		*philo;
	t_status	status;

	philo = (t_philo *)arg;
	ft_mutex_lock(&philo->mutex);
	philo->eat_last_time = get_time("ms");
	philo->is_set = true;
	ft_mutex_unlock(&philo->mutex);
	simulation_start(philo->table);
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 10);
	while (is_continue(philo->table, CONTINUE))
	{
		ft_mutex_lock(&philo->mutex);
		status = philo->status;
		ft_mutex_unlock(&philo->mutex);
		if (status == THINKING)
			philo_eat(philo);
		else if (status == EATING)
			philo_sleep(philo);
		else if (status == SLEEPING)
			philo_think(philo);
	}
	return (NULL);
}
