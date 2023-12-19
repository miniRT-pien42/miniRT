#include "libft.h"
#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h>

// todo: #12 perror
void	error_exit(const char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
