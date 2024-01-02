#include "error.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**x_ft_split(char const *str, const char *charset)
{
	char	**split_str;

	if (str == NULL)
		return (NULL);
	split_str = ft_split(str, charset);
	if (split_str == NULL)
	{
		putstr_with_endl(ERR_MESSAGE);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (split_str);
}
