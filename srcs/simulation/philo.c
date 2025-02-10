#include "philo.h"

bool is_continue(t_philo *philo, t_continue status)
{
    ft_mutex_lock(&philo->table->continue_mutex);
    if (status != CONTINUE)
        philo->table->stop = 1;
    if (philo->table->stop)
    {
        ft_mutex_unlock(&philo->table->continue_mutex);
        return (false);
    }
    ft_mutex_unlock(&philo->table->continue_mutex);
    return (true);
}

void philo_print(t_philo *philo, char *message)
{
    long time;

    ft_mutex_lock(&philo->table->print_mutex);
    time = get_time("ms") - philo->table->start_time;
    if (!philo->table->stop && time >= 0 && time <= INT_MAX && is_continue(philo, CONTINUE))
        printf("%ld %d %s\n", time, philo->id, message);
    ft_mutex_unlock(&philo->table->print_mutex);
}

void pick_fork(t_philo *philo)
{
    ft_mutex_lock(&philo->left->fork);
    philo_print(philo, "has taken a fork");
    if (philo->table->philo_nbr == 1)
    {
        ft_usleep(philo->table->time_to_die);
        return ;
    }
    ft_mutex_lock(&philo->right->fork);
    philo_print(philo, "has taken a fork");
}

void philo_eat(t_philo *philo)
{
    philo_print(philo, "is eating");
    ft_mutex_lock(&philo->table->m_eat);
    philo->last_eat = get_time("ms");
    philo->meal_count++;
    ft_mutex_unlock(&philo->table->m_eat);
    ft_usleep(philo->table->time_to_eat);
    ft_mutex_unlock(&philo->right->fork);
    ft_mutex_unlock(&philo->left->fork);
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    pthread_t monitor;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->table->time_to_eat / 10);
    while (is_continue(philo, CONTINUE))
    {
        pthread_create(&monitor, NULL, check_dead, philo);
        pick_fork(philo);
        philo_eat(philo);
        philo_print(philo, "is sleeping");
        ft_usleep(philo->table->time_to_sleep);
        philo_print(philo, "is thinking");
        pthread_detach(monitor);
        if (philo->meal_count == philo->table->limit_meals)
        {
            ft_mutex_lock(&philo->table->m_stop);
            if (++philo->table->philo_eat == philo->table->philo_nbr)
            {
                ft_mutex_unlock(&philo->table->m_stop);
                is_continue(philo, STOP);
            }
            ft_mutex_unlock(&philo->table->m_stop);
            return (NULL);
        }
    }
    return (NULL);
}

void    philo_set(t_table *table)
{
    int index;
    t_philo *philo;

    index = 0;
    table->start_time = get_time("ms");
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        ft_thread_create(&philo->thread, philo_routine, philo);
        index++;
    }
}
