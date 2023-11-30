#include <stdlib.h>
#include "debug.h"

void	check_scene_value(t_scene *scene)
{
	size_t		i;
	void		*object_current;
	t_sphere	*sphere;
	t_plane		*plane;

	i = 0;
	object_current = scene->list_object;
	printf("** camera\n");
	printf("scene->camera->pos = (%f, %f, %f)\n", scene->camera->pos.x, scene->camera->pos.y, scene->camera->pos.z);
	printf("scene->camera->dir_n = (%f, %f, %f)\n", scene->camera->dir_n.x, scene->camera->dir_n.y, scene->camera->dir_n.z);
	printf("scene->camera->fov = %d\n", scene->camera->fov);

	printf("** light_ambient\n");
	printf("scene->light_ambient->bright = %f\n", scene->light_ambient->bright);
	printf("scene->light_ambient->color = (%hhu, %hhu, %hhu)\n", scene->light_ambient->color.r, scene->light_ambient->color.g, scene->light_ambient->color.b);

	printf("** light\n");
	printf("scene->light->pos = (%f, %f, %f)\n", scene->light->pos.x, scene->light->pos.y, scene->light->pos.z);
	printf("scene->light->bright = %f\n", scene->light->bright);

	while (object_current)
	{
		printf("** list_object:%zu %d\n", i, get_object_type(object_current));
		if (get_object_type(object_current) == SPHERE)
		{
			sphere = (t_sphere *)object_current;
			printf("object_current->center = (%f, %f, %f)\n", sphere->center.x, sphere->center.y, sphere->center.z);
			printf("object_current->diameter = %f\n", sphere->diameter);
			printf("object_current->color = (%hhu, %hhu, %hhu)\n", sphere->color.r, sphere->color.g, sphere->color.b);
			object_current = sphere->next;
		}
		else if (get_object_type(object_current) == PLANE)
		{
			plane = (t_plane *)object_current;
			printf("object_current->point = (%f, %f, %f)\n", plane->point.x, plane->point.y, plane->point.z);
			printf("object_current->dir_n = (%f, %f, %f)\n", plane->dir_n.x, plane->dir_n.y, plane->dir_n.z);
			printf("object_current->color = (%hhu, %hhu, %hhu)\n", plane->color.r, plane->color.g, plane->color.b);
			object_current = plane->next;
		}
		else
			exit (EXIT_FAILURE);
		i++;
	}
}
