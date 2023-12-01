#include <stdlib.h>
#include "libft.h"
#include "object.h"
#include "value_tmp.h"

t_plane	*init_plane(char *line)
{
	t_plane	*plane;

	(void)line;//todo: #3
	plane = (t_plane *)x_malloc(sizeof(t_plane));
	plane->type = PLANE1_TYPE;
	plane->point = (t_vector)PLANE1_POINT;
	plane->dir_n = (t_vector)PLANE1_DIR_N;
	plane->color = (t_rgb)PLANE1_COLOR;
	return (plane);
}
