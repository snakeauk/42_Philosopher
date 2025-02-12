#ifndef PHILO_H
# define PHILO_H

#include <stdio.h> // printf 
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep
#include <stdbool.h> // true false
#include <pthread.h> // mutex threads
#include <sys/time.h> // gettime of day
#include <stdbool.h> // true false
#include "utils.h"
typedef pthread_mutex_t t_mutex;

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
}               t_status;

typedef enum e_continue
{
    CONTINUE,
    DEAD,
    STOP,
}               t_continue;

typedef struct s_fork
{
    int id;
    t_mutex fork;
}               t_fork;

typedef struct s_philo
{
    int id;
    int meal_count;
    bool is_set;
    bool is_eating;
    long last_eat;
    pthread_t thread;
    t_mutex mutex;
    t_status status;
    struct s_table *table;
    struct s_fork *left;
    struct s_fork *right;
}               t_philo;

typedef struct s_monitor
{
    pthread_t monitor_thread;
    t_mutex mutex;
    bool    is_set;
}           t_moniotor;

typedef struct s_table
{
    int  philo_eat;
    int  philo_nbr;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long limit_meals;
    int stop;
    long start_time;
    t_fork *forks;
    t_philo *philos;
    t_moniotor monitor;
    t_mutex print_mutex;
    t_mutex m_stop;
    t_mutex m_eat;
    t_mutex continue_mutex;
}               t_table;

int check_input(int argc, char **argv);
int main(int argc, char **argv);

// init
int    init_arg(t_table *table, char **argv);
int init_table(t_table *table);

// simulation
void    simulation(t_table *table);
bool is_continue(t_table *table, t_continue status);
void philo_print(t_philo *philo, char *message);
void philo_start(t_table *table);
void    philo_set(t_table *table);
void *check_dead(void *arg);

// error
void    error_exit(char *message, t_table *table);
int error_message(char *message);

// free.c
void    free_table(t_table *table);


#endif
