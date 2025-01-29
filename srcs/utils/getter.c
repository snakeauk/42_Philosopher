#include "utils.h"

bool    get_bool(t_mutex *mutex, bool *value)
{
    bool    ret;
    int     status;

    status = ft_mutex_lock(mutex);
    if (status == EINVAL || status == EDEADLK)
        exit(EXIT_FAILURE);
    ret = *value;
    status = ft_mutex_unlock(mutex);
    if (status == EINVAL || status == EPERM)
        exit(EXIT_FAILURE);
    return (ret);
}

long    get_long(t_mutex *mutex, long *value)
{
    long    ret;
    int     status;

    status = ft_mutex_lock(mutex);
    if (status == EINVAL || status == EDEADLK)
        exit(EXIT_FAILURE);
    ret = *value;
    status = ft_mutex_unlock(mutex);
    if (status == EINVAL || status == EPERM)
        exit(EXIT_FAILURE);
    return (ret);
}
