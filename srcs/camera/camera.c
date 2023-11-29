#include "camera.h"
#include "libft.h"
#include "value_tmp.h" // todo: rm

t_camera	*init_camera(void)
{
	t_camera	*camera;

	camera = (t_camera *)x_malloc(sizeof(t_camera));
	camera->pos = (t_vector)CAMERA_POS;
	camera->dir_n = (t_vector)CAMERA_DIR_N;
	camera->fov = CAMERA_FOV;
	return (camera);
}
