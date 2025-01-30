#include "philo.h"

void    simulation_set(t_table *table)
{
    philo_set(table);
    monitor_set(table);
}


void    simulation(t_table *table)
{
    simulation_set(table);
    simulation_wait(table);
}
