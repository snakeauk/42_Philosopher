#include "utils.h"

int	error_thread(int status)
{
	if (EPERM == status)
		ft_fputs("The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.\n", STDERR_FILENO);
	else if (ESRCH == status)
		ft_fputs("No thread could be found corresponding to that specified by the given thread ID, thread.\n", STDERR_FILENO);
	else if (EDEADLK == status)
		ft_fputs("A deadlock was detected or the value of thread specifies the calling thread.\n", STDERR_FILENO);
	else if (ENOMEM == status)
		ft_fputs("The process cannot allocate enough memory to create another mutex.\n", STDERR_FILENO);
	else if (EINVAL == status)
		ft_fputs("value specified by mutex is invalid.\n", STDERR_FILENO);
	else if (EAGAIN == status)
		ft_fputs("system lacked the necessary resources to create another thread, or the system-imposed limit on the total number of threads in a process [PTHREAD_THREADS_MAX] would be exceeded.\n", STDERR_FILENO);
	return (status);
}

int	ft_thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg)
{
	int	status;

	status = pthread_create(thread, NULL, start_routine, arg);
	error_thread(status);
	return (status);
}

int	ft_thread_join(pthread_t thread)
{
	int	status;

	status = pthread_join(thread, NULL);
	error_thread(status);
	return (status);
}
