#include "libft.h"

size_t	ft_len_2d_array(const char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
