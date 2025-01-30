#ifndef PHILO_H
# define PHILO_H

#include <stdio.h> // printf 
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep
#include <stdbool.h> // true false
#include <pthread.h> // mutex threads
#include <sys/time.h> // gettime 
#include <limits.h>
#include <errno.h>

#include "utils.h"

typedef pthread_mutex_t t_mutex;
typedef struct s_table  t_table;

typedef enum e_state
{
    THINKING,
    EATING,
    SLEEPING,
    DEAD
}               t_state;

typedef struct s_fork
{
    int     fork_id;
    t_mutex fork;
}               t_fork;

typedef struct s_philo
{
    pthread_t       thread_id;
    t_mutex         philo_mutex;
    int             id;
    long            meals_counter;
    long            last_meal_time;
    long            last_sleep_time;
    long            next_eat_time;
    t_state         state;
    t_fork          *first_fork;
    t_fork          *second_fork;
    t_table         *table;
}               t_philo;

typedef struct s_monitor
{
    pthread_t   thread_id;
    t_mutex     monitor_mutex;
    bool        is_dead;
    bool        simulation_continue;
}           t_monitor;

typedef struct s_table
{
    long        philo_nbr;
    long        time_to_die;
    long        time_to_eat;
    long        time_to_sleep;
    long        limit_meals;
    long        start_time;
    long        interval;
    t_monitor   monitor;
    t_philo     *philos;
    t_fork      *forks;
}               t_table;

# define RESET    "\033[0m"   // Reset to default color
# define RED    "\033[1;31m" // Bold RED

// main.c
void        error_exit(char *message, t_table *table);
int         main(int argc, char **argv);

// init_arg.c
int    init_arg(t_table *table, char **argv);

// init_table.c
t_table     *init_table(int argc, char **argv);

// check.c
int         check_input(int argc, char **argv);

// free.c
void        free_table(t_table *table);

// philo.c
void    philo_set(t_table *table);


#endif
