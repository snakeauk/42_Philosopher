#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <limit.h>

typedef struct s_philo
{
    int             philo;
    struct s_philo  *next;
}               t_philo;

int main(int argc, char **argv);

#endif
