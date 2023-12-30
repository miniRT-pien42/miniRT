#include "error.h"
#include "helpers.h"
#include <fcntl.h> // open
#include <stdio.h>
#include <stdlib.h>

int	x_open(const char *path, int open_flag)
{
	int	ret;

	ret = open(path, open_flag);
	if (ret == OPEN_ERROR)
	{
		putstr_with_endl(ERR_MESSAGE);
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
