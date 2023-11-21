#include <stdio.h>
#include <stdlib.h> // exit

// todo: #12 perror
void	error_exit(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
