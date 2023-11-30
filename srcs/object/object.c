#include <stdlib.h>
#include <math.h>
#include "object.h"
#include "scene.h"
#include "ray.h"
#include "value_tmp.h"

//todo: #3 sp,pl,cyが複数ある場合はloopでまわす

void	*init_object(char *line)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_sphere	*current;

	sphere = init_sphere(line);
	plane = init_plane(line);
	current = sphere;
	while (current->next != NULL)
		current = (t_sphere *)current->next;
	current->next = plane;
	return (sphere);
}

t_shape	get_object_type(void *object)
{
	return (*(t_shape *)object);
}

t_intersection	get_nearest_object(t_vector ray, t_scene *scene)
{
	t_intersection	nearest;
	void			*object_current;
	t_sphere		*sphere;
	t_plane			*plane;

	nearest.distance = INFINITY;
	object_current = scene->list_object;
	while (object_current)
	{
		if (get_object_type(object_current) == SPHERE)
		{
			sphere = (t_sphere *)object_current;
			judge_nearest_sphere(ray, scene, sphere, &nearest);
			object_current = sphere->next;
		}
		else if (get_object_type(object_current) == PLANE)
		{
			plane = (t_plane *)object_current;
			judge_nearest_plane(ray, scene, plane, &nearest);
			object_current = plane->next;
		}
		else
			exit (EXIT_FAILURE);
	}
	return (nearest);
}
