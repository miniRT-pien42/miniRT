#include "camera.h"
#include "display.h"
#include "helpers.h"
#include "scene.h"
#include <math.h>

t_vector	set_axis_base(void)
{
	return ((t_vector){.x = AXIS_BASE_X, .y = AXIS_BASE_Y, .z = AXIS_BASE_Z});
}

t_vector	set_axis_rotate_base(void)
{
	return ((t_vector){\
		.x = AXIS_ROTATE_BASE_X, \
		.y = AXIS_ROTATE_BASE_Y, \
		.z = AXIS_ROTATE_BASE_Z});
}

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

	screen.x = 0;
	screen.y = 0;
	screen.center_screen = get_center_screen(scene->camera);
	screen.rotate_x = get_rotate_x(scene->camera->dir_norm);
	screen.rotate_y = get_rotate_y(scene->camera->dir_norm);
	return (screen);
}
