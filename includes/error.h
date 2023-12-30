#ifndef ERROR_H
# define ERROR_H

# define ERR_MESSAGE	"Error"
# define ERR_MLX		"mlx"
# define ERR_ARGS		"Invalid arguments"
# define ERR_FILEPATH	"Invalid filepath"
# define ERR_RTFILE		"Invalid .rt value"

/* error */
void	putstr_with_endl(const char *message);
void	error_exit(const char *message);

#endif
