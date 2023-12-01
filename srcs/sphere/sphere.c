#include "object.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <stdlib.h> // todo: rm (atof)
#include "value_tmp.h" // todo: remove

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

t_sphere	*init_sphere(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE1_TYPE;
	sphere->center = (t_vector)SPHERE1_CENTER;
	sphere->diameter = SPHERE1_DIAMETER;
	sphere->color = (t_rgb)SPHERE1_COLOR;
	return (sphere);
}

// static t_sphere	*init_sphere(const char **line)
// {
// 	t_sphere	*sphere;

// 	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
// 	sphere->type = SPHERE;
// 	sphere->center = convert_line_to_vector(line[1], ',');
// 	sphere->diameter = atof(line[2]);
// 	sphere->color = convert_line_to_rgb(line[3], ',');
// 	return (sphere);
// }

// void	add_to_list_object(t_scene *scene, const char **line)
// {
// 	t_sphere	*list_sphere;

// 	if (scene->list_sphere == NULL)
// 	{
// 		scene->list_sphere = init_sphere(line);
// 		return ;
// 	}
// 	list_sphere = scene->list_sphere;
// 	while (list_sphere->next)
// 		list_sphere = list_sphere->next;
// 	list_sphere->next = init_sphere(line);

// }
