#include <stdlib.h>
#include <math.h>
#include "object.h"
#include "scene.h"
#include "ray.h"
#include "value_tmp.h"

//todo: #3 sp,pl,cyが複数ある場合はloopでまわす

t_deque	*init_object(char *line)
{
	t_deque		*ret_object;

	ret_object = deque_new();
	deque_add_first_node(\
		ret_object, deque_node_new((t_sphere *)init_sphere(line)));
	deque_add_back(\
		ret_object, deque_node_new((t_sphere *)init_sphere2_tmp()));
	deque_add_back(\
		ret_object, deque_node_new((t_sphere *)init_sphere3_tmp()));
	deque_add_back(\
		ret_object, deque_node_new((t_plane *)init_plane(line)));
	return (ret_object);
}

t_shape	get_object_type(void *object)
{
	return (*(t_shape *)object);
}

t_intersection	get_nearest_object(t_vector ray, t_scene *scene)
{
	t_intersection	nearest;
	t_deque_node	*object_current;

	nearest.distance = INFINITY;
	object_current = scene->list_object->node;
	while (object_current)
	{
		if (get_object_type(object_current->content) == SPHERE)
		{
			judge_nearest_sphere(\
				ray, scene, (t_sphere *)object_current->content, &nearest);
		}
		else if (get_object_type(object_current->content) == PLANE)
		{
			judge_nearest_plane(\
				ray, scene, (t_plane *)object_current->content, &nearest);
		}
		else
			exit (EXIT_FAILURE);
		object_current = object_current->next;
	}
	return (nearest);
}
