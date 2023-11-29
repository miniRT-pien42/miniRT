#include <stdlib.h>
#include "debug.h"

void	check_scene_value(t_scene *scene)
{
	size_t		i;
	void	*object_current;

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

	while (1)
	{
		printf("** list_object:%zu\n", i);
		if (((t_sphere *)object_current)->shape == SPHERE)
		{
			printf("object_current->center = (%f, %f, %f)\n", ((t_sphere *)object_current)->center.x, ((t_sphere *)object_current)->center.y, ((t_sphere *)object_current)->center.z);
			printf("object_current->diameter = %f\n", ((t_sphere *)object_current)->diameter);
			printf("object_current->color = (%hhu, %hhu, %hhu)\n", ((t_sphere *)object_current)->color.r, ((t_sphere *)object_current)->color.g, ((t_sphere *)object_current)->color.b);
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
			printf("object_current->point = (%f, %f, %f)\n", ((t_plane *)object_current)->point.x, ((t_plane *)object_current)->point.y, ((t_plane *)object_current)->point.z);
			printf("object_current->dir_n = (%f, %f, %f)\n", ((t_plane *)object_current)->dir_n.x, ((t_plane *)object_current)->dir_n.y, ((t_plane *)object_current)->dir_n.z);
			printf("object_current->color = (%hhu, %hhu, %hhu)\n", ((t_plane *)object_current)->color.r, ((t_plane *)object_current)->color.g, ((t_plane *)object_current)->color.b);
			if (((t_plane *)object_current)->next == NULL)
				break ;
			if (((t_sphere *)((t_plane *)object_current)->next) \
				->shape == SPHERE)
				object_current = (t_sphere *)((t_plane *)object_current)->next;
			else if (((t_plane *)((t_plane *)object_current)->next) \
				->shape == PLANE)
				object_current = (t_plane *)((t_plane *)object_current)->next;
		}
		else
			exit (EXIT_FAILURE);
		i++;
	}
}
