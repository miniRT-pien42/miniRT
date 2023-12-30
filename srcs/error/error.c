#include "error.h"
#include "libft.h"
#include <stdlib.h> // exit
#include <unistd.h>

void	putstr_with_endl(const char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	error_exit(const char *message)
{
	putstr_with_endl(ERR_MESSAGE);
	putstr_with_endl(message);
	exit(EXIT_FAILURE);
}
