#include "utils.h"

int	ft_fputs(const char *s, int fd)
{
	int	ret;

	if (!s)
		ret = write(fd, "(null)", 6);
	else
		ret = write(fd, s, ft_strlen(s));
	if (ret < 0)
		return (-1);
	return (ret);
}
