#include "camera.h"
#include "debug.h"
#include "ft_deque.h"
#include "light.h"
#include "object.h"
#include "scene.h"
#include <stdio.h>
#include <stdlib.h>

void	debug_print_vector(const char *name, const t_vector vec)
{
	printf("%s = (%f, %f, %f)\n", name, vec.x, vec.y, vec.z);
}

void	debug_print_rgb(const char *name, const t_rgb rgb)
{
	printf("%s = (%hhu, %hhu, %hhu)\n", name, rgb.r, rgb.g, rgb.b);
}

static void	debug_print_camera_and_light(const t_scene *scene)
{
	printf("** camera\n");
	debug_print_vector("scene->camera->pos", scene->camera->pos);
	debug_print_vector("scene->camera->dir_norm", scene->camera->dir_norm);
	printf("scene->camera->fov = %d\n", scene->camera->fov);

	printf("** light_ambient\n");
	printf("scene->light_ambient->bright = %f\n", scene->light_ambient->bright);
	debug_print_rgb("scene->light_ambient->color", scene->light_ambient->color);

	printf("** light\n");
	debug_print_vector("scene->light->pos", scene->light->pos);
	printf("scene->light->bright = %f\n", scene->light->bright);
	debug_print_rgb("scene->light->color", scene->light->color);
}

static void	debug_print_object(const t_scene *scene)
{
	size_t			i;
	t_deque_node	*object_current;
	t_shape			type;

	i = 0;
	object_current = scene->list_object->node;
	printf("** deque_print\n");
	while (object_current)
	{
		type = get_object_type(object_current->content);
		printf("** list_object:%zu %d\n", i, type);
		if (type == SPHERE)
			debug_print_sphere((t_sphere *)object_current->content);
		else if (type == PLANE)
			debug_print_plane((t_plane *)object_current->content);
		else if (type == CYLINDER)
			debug_print_cylinder((t_cylinder *)object_current->content);
		else
		{
			printf("Error: unknown object\n");
			exit(EXIT_FAILURE);
		}
		object_current = object_current->next;
		i++;
	}
}

void	debug_print_scene_value(const t_scene *scene)
{
	debug_print_camera_and_light(scene);
	debug_print_object(scene);
}
