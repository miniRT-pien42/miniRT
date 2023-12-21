#include <math.h>
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

//カメラのorientation vectorの延長線上にあり、WIDTHが2の画角を取れる平面の中心座標
// (WIDTH=2のとき画角のWIDTHが円錐に外接する)
t_vector	get_center_screen(t_camera *camera)
{
	double	diameter;
	double	t;

	if (camera->fov == 0 || camera->fov == 180)
		return (camera->pos);
	diameter = 2.0;
	t = (diameter / 2) / tan(convert_deg_to_rad(camera->fov / 2.0));
	return (vec_add(camera->pos, vec_scalar(camera->dir_n, t)));
}
