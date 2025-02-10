#include "philo.h"

void *check_dead(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    ft_usleep(philo->table->time_to_die + 1);
    ft_mutex_lock(&philo->table->m_eat);
    ft_mutex_lock(&philo->table->m_stop);
    if (is_continue(philo, CONTINUE) && get_time("ms") - philo->last_eat >= philo->table->time_to_die)
    {
        ft_mutex_unlock(&philo->table->m_eat);
        ft_mutex_unlock(&philo->table->m_stop);
        philo_print(philo, "died");
        is_continue(philo, STOP);
    }
    ft_mutex_unlock(&philo->table->m_eat);
    ft_mutex_unlock(&philo->table->m_stop);
    return (NULL);
}
