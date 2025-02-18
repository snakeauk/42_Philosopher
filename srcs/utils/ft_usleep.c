#include "utils.h"

void ft_usleep(long time)
{
	long	start;

	start = get_time("ms");
	while (get_time("ms") - start < time)
		usleep(time / 10);
}
