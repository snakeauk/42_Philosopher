#include "philo.h"

void *check_dead(void *arg)
{
    t_philo *philo;
    t_table *table;
    int     index;

    table = (t_table *)arg;
    ft_mutex_lock(&table->monitor.mutex);
    table->monitor.is_set = true;
    ft_mutex_unlock(&table->monitor.mutex);
    table->start_time = get_time("ms");
    philo_start(table);
    while (is_continue(table, CONTINUE))
    {
        index = 0;
        while (is_continue(table, CONTINUE) && index < table->philo_nbr)
        {
            philo = &table->philos[index];
            ft_usleep(philo->table->time_to_die + 1);
            ft_mutex_lock(&philo->table->m_eat);
            ft_mutex_lock(&philo->table->m_stop);
            if (is_continue(table, CONTINUE) && get_time("ms") - philo->last_eat >= philo->table->time_to_die)
            {
                philo_print(philo, "died");
                is_continue(table, STOP);
            }
            ft_mutex_unlock(&philo->table->m_eat);
            ft_mutex_unlock(&philo->table->m_stop);
            index++;
        }
        ft_usleep(table->time_to_die / 10);
    }
    return (NULL);
}

// void *check_dead(void *arg)
// {
//     t_philo *philo;

//     philo = (t_philo *)arg;
//     ft_usleep(philo->table->time_to_die + 1);
//     ft_mutex_lock(&philo->table->m_eat);
//     ft_mutex_lock(&philo->table->m_stop);
//     if (is_continue(philo, CONTINUE) && get_time("ms") - philo->last_eat >= philo->table->time_to_die)
//     {
//         ft_mutex_unlock(&philo->table->m_eat);
//         ft_mutex_unlock(&philo->table->m_stop);
//         philo_print(philo, "died");
//         is_continue(philo, STOP);
//     }
//     ft_mutex_unlock(&philo->table->m_eat);
//     ft_mutex_unlock(&philo->table->m_stop);
//     return (NULL);
// }
