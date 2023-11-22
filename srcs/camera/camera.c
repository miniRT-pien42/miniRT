#include <stdlib.h>
#include "camera.h"
#include "value_tmp.h"

t_camera	*init_camera(char *line)
{
	t_camera	*camera;

	(void)line;//todo: #3
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->pos = (t_vector)CAMERA_POS;
	camera->dir_n = (t_vector)CAMERA_DIR_N;
	camera->fov = CAMERA_FOV;
	return (camera);
}
