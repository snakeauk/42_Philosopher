#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/time.h>

// time
long	get_time(char *timecode);

// usleep
void	ft_usleep(long time);

// thread
typedef pthread_mutex_t	t_mutex;
int		ft_thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg);
int		ft_thread_join(pthread_t thread);
int		error_thread(int status);

// mutex
int		ft_mutex_init(t_mutex *mutex);
int		ft_mutex_lock(t_mutex *mutex);
int		ft_mutex_unlock(t_mutex *mutex);

// utils
long	ft_atol(const char *str);
int		ft_fputs(const char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_hextoi(int c);
int		ft_isdigit(int c);
int		ft_ishexdigit(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
long	ft_strtol(const char *str, char **endptr, int base);

// getter_setter.c
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *value);
void	set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);

#endif
