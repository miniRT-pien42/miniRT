#include <stdio.h>

void	print_2d_array(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		printf("%s   ", strs[i]);
		i++;
	}
}
