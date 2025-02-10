#include "utils.h"

long	ft_atol(const char *str)
{
	return (ft_strtol(str, NULL, 10));
}
