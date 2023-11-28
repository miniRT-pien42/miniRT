#include <stdlib.h>
#include "object.h"
#include "value_tmp.h"

//todo: #3 spが複数ある場合はloopでまわす

static t_sphere	*init_sphere3_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = (t_vector)SPHERE3_CENTER;
	sphere->diameter = SPHERE3_DIAMETER;
	sphere->color = (t_rgb)SPHERE3_COLOR;
	sphere->is_camera_inside = false;
	sphere->is_light_inside = false;
	sphere->next = NULL;
	return (sphere);
}

static t_sphere	*init_sphere2_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = (t_vector)SPHERE2_CENTER;
	sphere->diameter = SPHERE2_DIAMETER;
	sphere->color = (t_rgb)SPHERE2_COLOR;
	sphere->is_camera_inside = false;
	sphere->is_light_inside = false;
	sphere->next = init_sphere3_tmp();
	return (sphere);
}

t_sphere	*init_sphere(char *line)
{
	t_sphere	*sphere;

	(void)line;//todo: #3
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = (t_vector)SPHERE1_CENTER;
	sphere->diameter = SPHERE1_DIAMETER;
	sphere->color = (t_rgb)SPHERE1_COLOR;
	sphere->is_camera_inside = false;
	sphere->is_light_inside = false;
	sphere->next = init_sphere2_tmp();
	return (sphere);
}
