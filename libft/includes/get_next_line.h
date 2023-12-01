#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include "../../includes/result.h"

# define READ_ERROR	(-1)
# define LF			'\n'
# define CHR_NULL	'\0'

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif

char	*get_next_line(int fd, t_result *result);

#endif
