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

t_intersection	get_nearest_object(t_vector ray, t_scene *scene)
{
	t_intersection	nearest;
	void			*object_current;

	nearest.distance = INFINITY;
	object_current = scene->list_object;
	while (1)
	{
		if (((t_sphere *)object_current)->shape == SPHERE)
		{
			judge_nearest_sphere(ray, scene, object_current, &nearest);
			if (((t_sphere *)object_current)->next == NULL)
				break ;
			if (((t_sphere *)((t_sphere *)object_current)->next) \
				->shape == SPHERE)
				object_current = (t_sphere *)((t_sphere *)object_current)->next;
			else if (((t_plane *)((t_sphere *)object_current)->next) \
				->shape == PLANE)
				object_current = (t_plane *)((t_sphere *)object_current)->next;
		}
		else if (((t_plane *)object_current)->shape == PLANE)
		{
			judge_nearest_plane(ray, scene, object_current, &nearest);
			if (((t_plane *)object_current)->next == NULL)
				break ;
			if (((t_sphere *)((t_plane *)object_current)->next) \
				->shape == SPHERE)
				object_current = (t_sphere *)((t_sphere *)object_current)->next;
			else if (((t_plane *)((t_plane *)object_current)->next) \
				->shape == PLANE)
				object_current = (t_plane *)((t_plane *)object_current)->next;
		}
		else
			exit (EXIT_FAILURE);
	}
	return (nearest);
}
