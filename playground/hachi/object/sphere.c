
#include "../include/primitive.h"

ssize_t	extract_closest(double *list_distance, size_t size)
{
	size_t	i;
	ssize_t	closest;

	i = 0;
	closest = -1;
	while (closest == -1 && i < size)
	{
		if (list_distance[i] >= 0)
			closest = i;
		i++;
	}
	while (i < size)
	{
		if (list_distance[i] >= 0 && list_distance[i] < list_distance[closest])
			closest = i;
		i++;
	}
	return (closest);
}