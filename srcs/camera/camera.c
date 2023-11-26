#include <stdlib.h>
#include <math.h>
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

//カメラのorientation vectorの延長線上にあり、WIDTHが2の画角を取れる平面の中心座標
t_vector	get_center_screen(t_camera *camera)
{
	double	diameter;
	double	t;

	diameter = sqrt(pow(WIDTH * 2 / WIDTH, 2) + pow(HEIGHT * 2 / WIDTH, 2));
	t = (diameter / 2) / tan(convert_deg_to_rad(camera->fov / 2.0));
	return (vec_add(camera->pos, (t_vector){0, 0, t}));

}
