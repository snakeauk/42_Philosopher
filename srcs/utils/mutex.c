#include "utils.h"

int ft_mutex_init(t_mutex *mutex)
{
	int status;

	status = pthread_mutex_init(mutex, NULL);
	error_thread(status);
	return (status);
}

int ft_mutex_unlock(t_mutex *mutex)
{
	int status;

	status = pthread_mutex_unlock(mutex);
	error_thread(status);
	return (status);
}

int ft_mutex_lock(t_mutex *mutex)
{
	int status;

	status = pthread_mutex_lock(mutex);
	error_thread(status);
	return (status);
}
