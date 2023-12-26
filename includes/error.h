#ifndef ERROR_H
# define ERROR_H

# define ERR_MLX		"Error: mlx"
# define ERR_ARGS		"Error: Invalid arguments"
# define ERR_FILEPATH	"Error: Invalid filepath"
# define ERR_RTFILE		"Error: Invalid .rt value"
# define ERR_INTERSECTION		"Error: wrong intersection"

void	error_exit(const char *message);

#endif
