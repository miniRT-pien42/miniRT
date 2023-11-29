#include <stddef.h>
#include <stdio.h>
#include "debug.h"

void	debug_print_scene_value(const t_scene *scene)
{
	size_t		i;
	t_sphere	*sphere_current;

	i = 0;
	sphere_current = scene->list_sphere;
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

	while (sphere_current)
	{
		printf("** list_sphere:sphere%zu\n", i);
		printf("sphere_current->center = (%f, %f, %f)\n", sphere_current->center.x, sphere_current->center.y, sphere_current->center.z);
		printf("sphere_current->diameter = %f\n", sphere_current->diameter);
		printf("sphere_current->color = (%hhu, %hhu, %hhu)\n", sphere_current->color.r, sphere_current->color.g, sphere_current->color.b);
		sphere_current = sphere_current->next;
		i++;
	}
}
