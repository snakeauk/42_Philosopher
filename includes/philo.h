#ifndef PHILO_H
# define PHILO_H

#include <stdio.h> // printf 
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep
#include <stdbool.h>
#include <pthread.h> // mutex threads
#include <sys/time.h> // gettime 
#include <limits.h>

typedef pthread_mutex_t t_mutex;
typedef strcut s_fork;
typedef struct s_table;
typedef struct s_philo;

typedef strcut s_fork{
    t_mutex fork;
    int     fork_id;
}               t_fork;

typedef struct s_philo
{
    int             id;
    long            meals_counter;
    bool            full;
    long            last_meal_time;
    t_fork          *left_fork;
    t_fork          *right_fork;
    pthread_t       thred_id;
}               t_philo;

typedef struct s_table
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    logn    nbr_limit_meals;
    long    start_simulation;
    bool    end_simulation;
    t_fork  *forks;
    t_philo *philos;
}               t_table;

int main(int argc, char **argv);

#endif
