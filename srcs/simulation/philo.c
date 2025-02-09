#include "philo.h"

int philo_log(t_philo *philo, char *message)
{
    int status;
    long time;

    status = 0;
    ft_mutex_lock(&philo->philo_mutex);
    time = get_time("ms") - philo->table->start_time;
    printf("%ld %d %s\n", time, philo->id, message);
    ft_mutex_unlock(&philo->philo_mutex);
    return (status);
}

int pickup_forks(t_philo *philo)
{
    int status;

    ft_mutex_lock(&philo->first_fork->fork);
    status = philo_log(philo, "has taken a fork");
    if (status == 0)
    {
        ft_mutex_lock(&philo->second_fork->fork);
        status = philo_log(philo, "has taken a fork");
        if (status != 0)
            ft_mutex_unlock(&philo->first_fork->fork);
    }
    if (status != 0)
        ft_mutex_unlock(&philo->first_fork->fork);
    return (status);
}

int philo_eat(t_philo *philo)
{
    int status;

    philo->state = EATING;
    status = pickup_forks(philo);
    if (status == 0)
    {
        ft_mutex_lock(&philo->philo_mutex);
        philo->meals_counter++;
        status = philo_log(philo, "is eating");
        ft_mutex_unlock(&philo->philo_mutex);
        philo->next_eat_time = get_time("ms") + philo->table->interval;
        if (status == 0)
            usleep(philo->table->time_to_eat);
        ft_mutex_unlock(&philo->first_fork->fork);
        ft_mutex_unlock(&philo->second_fork->fork);
    }
    return (status);
}

int philo_sleep(t_philo *philo)
{
    int status;
    int sleep_time;

    philo->state = SLEEPING;
    status = philo_log(philo, "is sleeping");
    if (status == 0)
    {
        sleep_time = philo->table->time_to_sleep;
        usleep(sleep_time);
    }
    return (status);
}

int philo_think(t_philo *philo)
{
    int status;

    philo->state = THINKING;
    status = philo_log(philo, "is thinking");
    if (status == 0)
        usleep(philo->next_eat_time);
    return (status);
}

int is_dead(t_philo *philo)
{
    int status;

    status = 0;
    ft_mutex_lock(&philo->philo_mutex);
    if (get_time("ms") - philo->last_meal_time > philo->table->time_to_die)
        philo->state = DEAD;
    ft_mutex_unlock(&philo->philo_mutex);
    return (status);
}

void    wait_start(t_table *table)
{
    t_monitor *monitor;

    monitor = &table->monitor;
    while (get_bool(&monitor->monitor_mutex, &monitor->simulation_continue) == false)
        ;
}

void    *philo_routine(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    set_bool(&philo->philo_mutex, &philo->is_set, true);
    wait_start(table);
    while (get_bool(&table->monitor.monitor_mutex, &table->monitor.simulation_continue))
    {
        is_dead(philo);
        if (philo->state == THINKING)
            philo_eat(philo);
        if (philo->state == EATING)
            philo_sleep(philo);
        if (philo->state == SLEEPING)
            philo_think(philo);
        else
            usleep(100);
    }
    return (NULL);
}

void    philo_set(t_table *table)
{
    int index;
    t_philo *philo;

    index = 0;
    while (index < table->philo_nbr)
    {
        philo = &table->philos[index];
        ft_thread_create(&philo->thread_id, philo_routine, philo);
        index++;
    }
}
