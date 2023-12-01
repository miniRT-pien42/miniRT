#include <stdlib.h>
#include "object.h"
#include "value_tmp.h"

t_sphere	*init_sphere3_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);

	sphere->type = SPHERE3_TYPE;
	sphere->center = (t_vector)SPHERE3_CENTER;
	sphere->diameter = SPHERE3_DIAMETER;
	sphere->color = (t_rgb)SPHERE3_COLOR;
	return (sphere);
}

t_sphere	*init_sphere2_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE2_TYPE;
	sphere->center = (t_vector)SPHERE2_CENTER;
	sphere->diameter = SPHERE2_DIAMETER;
	sphere->color = (t_rgb)SPHERE2_COLOR;
	return (sphere);
}

t_sphere	*init_sphere(char *line)
{
	t_sphere	*sphere;

	(void)line;//todo: #3
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE1_TYPE;
	sphere->center = (t_vector)SPHERE1_CENTER;
	sphere->diameter = SPHERE1_DIAMETER;
	sphere->color = (t_rgb)SPHERE1_COLOR;
	return (sphere);
}
