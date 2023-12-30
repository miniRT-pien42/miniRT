#include "error.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

char	*x_get_next_line(int fd)
{
	bool	is_error;
	char	*line;

	is_error = false;
	line = get_next_line(fd, &is_error);
	if (is_error)
	{
		putstr_with_endl(ERR_MESSAGE);
		perror("read");
		exit(EXIT_FAILURE);
	}
	return (line);
}
