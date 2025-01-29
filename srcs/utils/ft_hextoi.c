#include "utils.h"

int	ft_hextoi(int c)
{
	if (ft_isdigit(c))
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (-1);
}