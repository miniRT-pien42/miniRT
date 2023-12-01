#include "object.h"
#include "libft.h"
#include "parse.h"
#include "value_tmp.h" // todo: rm
#include <stdlib.h> // todo: rm (atof)

//todo: #3 spが複数ある場合はloopでまわす

static t_sphere	*init_sphere3_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
	sphere->center = (t_vector)SPHERE3_CENTER;
	sphere->diameter = SPHERE3_DIAMETER;
	sphere->color = (t_rgb)SPHERE3_COLOR;
	sphere->next = NULL;
	return (sphere);
}

static t_sphere	*init_sphere2_tmp(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
	sphere->center = (t_vector)SPHERE2_CENTER;
	sphere->diameter = SPHERE2_DIAMETER;
	sphere->color = (t_rgb)SPHERE2_COLOR;
	sphere->next = init_sphere3_tmp();
	return (sphere);
}

t_sphere	*init_sphere(const char **line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
	sphere->center = convert_line_to_vector(line[1], ',');
	sphere->diameter = atof(line[2]);
	sphere->color = convert_line_to_rgb(line[3], ',');
	sphere->next = init_sphere2_tmp();
	return (sphere);
}
