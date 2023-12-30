#include "libft.h"
#include "object.h"
#include "parse.h"
#include "result.h"

t_plane	*init_plane(const char **line, t_result *result)
{
	t_plane	*plane;

	*result = SUCCESS;
	plane = (t_plane *)x_malloc(sizeof(t_plane));
	plane->type = PLANE;
	plane->point = convert_line_to_vector(line[0], result);
	plane->dir_n = init_normal_vector(line[1], DIR_N_MIN, DIR_N_MAX, result);
	plane->color = convert_line_to_rgb(line[2], result);
	return (plane);
}
