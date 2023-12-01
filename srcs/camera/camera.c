#include "camera.h"
#include "libft.h"
#include "parse.h"
#include <stdlib.h> // todo: rm (atof)

t_camera	*init_camera(const char **line)
{
	t_camera	*camera;

	camera = (t_camera *)x_malloc(sizeof(t_camera));
	camera->pos = convert_line_to_vector(line[1], ',');
	camera->dir_n = convert_line_to_vector(line[2], ',');
	camera->fov = atof(line[3]);
	return (camera);
}
