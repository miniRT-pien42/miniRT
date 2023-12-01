#include <stdlib.h>
#include <stdio.h>

void	*x_malloc(const size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (ptr == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
