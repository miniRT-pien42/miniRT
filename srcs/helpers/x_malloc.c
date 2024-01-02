#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void	*x_malloc(const size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (ptr == NULL)
	{
		putstr_with_endl(ERR_MESSAGE);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
