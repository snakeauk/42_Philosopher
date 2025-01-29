#include "utils.h"

void    set_bool(t_mutex *mutex, bool *dest, bool value)
{
    int status;

    status = ft_mutex_lock(mutex);
    if (status == EINVAL || status == EDEADLK)
        exit(EXIT_FAILURE);
    *dest = value;
    status = ft_mutex_unlock(mutex);
    if (status == EINVAL || status == EPERM)
        exit(EXIT_FAILURE);
}

void    set_long(t_mutex *mutex, long *dest, long value)
{
    int     status;

    status = ft_mutex_lock(mutex);
    if (status == EINVAL || status == EDEADLK)
        exit(EXIT_FAILURE);
    *dest = value;
    status = ft_mutex_unlock(mutex);
    if (status == EINVAL || status == EPERM)
        exit(EXIT_FAILURE);
}
