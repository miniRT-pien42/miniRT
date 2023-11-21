#include <stdlib.h>
#include "object.h"

//todo: #3 spが複数ある場合はloopでまわす

static t_sphere	*init_sphere3_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = (t_vector){-5, 0, -5};
	sphere->diameter = 0.5;
	sphere->color = (t_rgb){255, 255, 10};
	sphere->next = NULL;
	return (sphere);
}

static t_sphere	*init_sphere2_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = (t_vector){5, 0, 5};
	sphere->diameter = 0.5;
	sphere->color = (t_rgb){10, 255, 255};
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
	sphere->center = (t_vector){0, 0, 0};
	sphere->diameter = 1.6;
	sphere->color = (t_rgb){255, 10, 10};
	sphere->next = init_sphere2_tmp();
	return (sphere);
}
