#include "philo.h"

bool is_continue(t_table *table, t_continue status)
{
    ft_mutex_lock(&table->continue_mutex);
    if (status == STOP || status == DEAD)
        table->stop = true;
    if (table->stop)
    {
        ft_mutex_unlock(&table->continue_mutex);
        return (false);
    }
    ft_mutex_unlock(&table->continue_mutex);
    return (true);
}

void philo_print(t_philo *philo, char *message)
{
    long time;

    ft_mutex_lock(&philo->table->print_mutex);
    time = get_time("ms") - philo->table->start_time;
    if (!philo->table->stop && time >= 0 && time <= INT_MAX && is_continue(philo->table, CONTINUE))
        printf("%ld %d %s\n", time, philo->id, message);
    ft_mutex_unlock(&philo->table->print_mutex);
}

void philo_eat(t_philo *philo)
{
    philo->status = EATING;
    ft_mutex_lock(&philo->left->fork);
    philo_print(philo, "has taken a fork");
    if (philo->table->philo_nbr == 1)
    {
        ft_mutex_unlock(&philo->left->fork);
        ft_usleep(philo->table->time_to_die);
        return ;
    }
    ft_mutex_lock(&philo->right->fork);
    philo_print(philo, "has taken a fork");
    philo_print(philo, "is eating");
    ft_mutex_lock(&philo->table->m_eat);
    philo->last_eat = get_time("ms");
    philo->meal_count++;
    ft_mutex_unlock(&philo->table->m_eat);
    ft_usleep(philo->table->time_to_eat);
    ft_mutex_unlock(&philo->right->fork);
    ft_mutex_unlock(&philo->left->fork);
}

void    philo_sleep(t_philo *philo)
{
    philo->status = SLEEPING;
    philo_print(philo, "is sleeping");
    ft_usleep(philo->table->time_to_sleep);
}

void   philo_think(t_philo *philo)
{
    philo->status = THINKING;
    philo_print(philo, "is thinking");
}

void philo_move(t_philo *philo)
{
    if (philo->status == THINKING)
        philo_eat(philo);
    if (philo->status == EATING)
        philo_sleep(philo);
    if (philo->status == SLEEPING)
        philo_think(philo);
}

bool    is_start(t_table *table)
{
    t_philo *philo;
    bool is_set;
    int index;

    index = 0;
    is_set = false;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        ft_mutex_lock(&philo->mutex);
        is_set = philo->is_set;
        ft_mutex_unlock(&philo->mutex);
        if (!is_set)
            return (false);
        index++;
    } 
    return (true);
}

bool is_monitor_start(t_table *table)
{
    bool is_start;

    ft_mutex_lock(&table->monitor.mutex);
    is_start = table->monitor.is_set;
    table->start_time = get_time("ms");
    ft_mutex_unlock(&table->monitor.mutex);
    if (!is_start)
        return (false);
    return (true);
}

void philo_start(t_table *table)
{
    while (!is_start(table))
        ;
    while (!is_monitor_start(table))
        ;
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    ft_mutex_lock(&philo->mutex);
    philo->is_set = true;
    ft_mutex_unlock(&philo->mutex);
    philo_start(philo->table);
    philo_think(philo);
    if (philo->id % 2 == 0)
        ft_usleep(philo->table->time_to_eat / 10);
    while (is_continue(philo->table, CONTINUE))
    {
        philo_move(philo);
        if (philo->meal_count == philo->table->limit_meals)
        {
            ft_mutex_lock(&philo->table->m_stop);
            if (++philo->table->philo_eat == philo->table->philo_nbr)
            {
                ft_mutex_unlock(&philo->table->m_stop);
                is_continue(philo->table, STOP);
            }
            ft_mutex_unlock(&philo->table->m_stop);
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
