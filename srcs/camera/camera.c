#include <stdlib.h>
#include "camera.h"

t_camera	*init_camera(char *line)
{
	t_camera	*camera;

	(void)line;//todo: #3
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->pos = (t_vector){0, 0, -5};
	camera->dir_n = (t_vector){0, 0, 1};
	camera->fov = 60;
	return (camera);
}
