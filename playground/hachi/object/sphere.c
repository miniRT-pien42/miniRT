
#include "../include/sphere.h"

size_t	extract_closest(size_t *list_distance, size_t size)
{
	size_t	i;
	size_t	closest;

	i = 1;
	closest = 0;
	while (i < size)
	{
		if (list_distance[i] < list_distance[closest])
			closest = i;
		i++;
	}
	return (closest);
}