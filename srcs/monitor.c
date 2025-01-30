#include "philo.h"

bool    is_continue(t_table *table)
{
    bool    is_dead;
    bool    is_end;
    int     index;

    is_dead = false;
    is_end = false;
    index = 0;
    while (!is_dead && is_end && index < table->philo_nbr)
    {
        ft_mutex_lock(&table->philos[index].philo_mutex);
        if (table->philos[index].state == DEAD)
        {
            is_dead = true;
            philo_log(&table->philos[index], "is dead");
            ft_mutex_unlock(&table->philos[index].philo_mutex);
            break;
        }
        if (table->limit_meals != -1 && table->philos[index].meals_counter >= table->limit_meals)
            is_end = true;
        ft_mutex_unlock(&table->philos[index].philo_mutex);
    }
    if (!is_dead || !is_end)
        return (true);
    return (false);
}

void    check_start(t_table *table)
{
    int     index;
    t_philo *philo;
    bool    status;
    bool    start;

    index = 0;
    while (start)
    {
        start = false;
        while (index < table->philo_nbr)
        {
            status = false;
            philo = &table->philos[index];
            ft_mutex_lock(&philo->philo_mutex);
            status = philo->is_set;
            if (status == false)
                start = true;
            ft_mutex_unlock(&philo->philo_mutex);
            index++;
        }
    }
    table->start_time = get_time("ms");
}

void    *monitor_routine(void *arg)
{
    t_table *table;
    t_monitor *monitor;

    table = (t_table *)arg;
    monitor = &table->monitor;
    check_start(table);
    while (get_bool(&monitor->monitor_mutex, &monitor->simulation_continue))
    {
        usleep(1000);
        set_bool(&table->monitor.monitor_mutex, &table->monitor.simulation_continue, is_continue(table));
    }
    return (NULL);
}

void    *monitor_set(t_table *table)
{
    t_monitor *monitor;

    monitor = &table->monitor;
    ft_mutex_init(&monitor->monitor_mutex);
    ft_thread_create(&monitor->thread_id, monitor_routine, table);
    return (NULL);
}

