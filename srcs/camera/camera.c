#include "camera.h"
#include "helpers.h"
#include "parse.h"

t_camera	*init_camera(const char **line, t_result *result)
{
	t_camera	*camera;

	*result = SUCCESS;
	camera = (t_camera *)x_malloc(sizeof(t_camera));
	camera->pos = convert_line_to_vector(line[0], result);
	camera->dir_norm = \
		init_normal_vector(line[1], DIR_N_MIN, DIR_N_MAX, result);
	camera->fov = convert_to_uint8_in_range(line[2], FOV_MIN, FOV_MAX, result);
	return (camera);
}
