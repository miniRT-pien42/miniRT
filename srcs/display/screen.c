#include "camera.h"
#include "display.h"
#include "helpers.h"
#include "scene.h"
#include <math.h>

static t_vector	set_axis_base(void)
{
	return ((t_vector){.x = AXIS_BASE_X, .y = AXIS_BASE_Y, .z = AXIS_BASE_Z});
}

//カメラのorientation vectorの延長線上にあり、WIDTHが2の画角を取れる平面の中心座標
// (WIDTH=2のとき画角のWIDTHが円錐に外接する)
static t_vector	get_center_screen(t_camera *camera)
{
	double	diameter;
	double	t;

	if (camera->fov == 0 || camera->fov == 180)
		return (camera->pos);
	diameter = 2.0;
	t = (diameter / 2) / tan(convert_deg_to_rad(camera->fov / 2.0));
	return (vec_add(camera->pos, vec_scalar(camera->dir_norm, t)));
}

t_screen_info	get_screen_info(t_scene *scene)
{
	t_screen_info	screen;
	double			rotation_angle;
	t_vector		r_axis;

	screen.x = 0;
	screen.y = 0;
	screen.axis = set_axis_base();
	screen.center_screen = get_center_screen(scene->camera);
	rotation_angle = \
		vec_angle(set_axis_base(), scene->camera->dir_norm);
	r_axis = vec_normalize(vec_cross(screen.axis, scene->camera->dir_norm));
	screen.q_rotate = get_rotate_quaternion(r_axis, rotation_angle);
	return (screen);
}
