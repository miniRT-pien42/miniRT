#include "object.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <stdlib.h> // todo: rm (atof)

static t_sphere	*init_sphere(const char **line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)x_malloc(sizeof(t_sphere));
	sphere->center = convert_line_to_vector(line[1], ',');
	sphere->diameter = atof(line[2]);
	sphere->color = convert_line_to_rgb(line[3], ',');
	sphere->next = NULL;
	return (sphere);
}

void	add_to_list_sphere(t_scene *scene, const char **line)
{
	t_sphere	*list_sphere;

	if (scene->list_sphere == NULL)
	{
		scene->list_sphere = init_sphere(line);
		return ;
	}
	list_sphere = scene->list_sphere;
	while (list_sphere->next)
		list_sphere = list_sphere->next;
	list_sphere->next = init_sphere(line);
}
