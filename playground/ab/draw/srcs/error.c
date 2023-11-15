#include <stdio.h>
#include <stdlib.h> // exit

// todo: perror
void	error_exit(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
