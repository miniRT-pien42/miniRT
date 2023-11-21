
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "ray.h"
#include "vector.h"
#include "display.h"

#define WIDTH 512
#define HEIGHT 512

static void	check_scene_value(t_scene *scene)
{
	size_t		i;
	t_sphere	*sphere_cr;

	i = 0;
	sphere_cr = scene->list_sphere;
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

	while (sphere_cr)
	{
		printf("** list_sphere:sphere%zu\n", i);
		printf("sphere_cr->center = (%f, %f, %f)\n", sphere_cr->center.x, sphere_cr->center.y, sphere_cr->center.z);
		printf("sphere_cr->diameter = %f\n", sphere_cr->diameter);
		printf("sphere_cr->color = (%hhu, %hhu, %hhu)\n", sphere_cr->color.r, sphere_cr->color.g, sphere_cr->color.b);
		sphere_cr = sphere_cr->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_scene		*scene;

	(void) argc;
	scene = init_scene(argv[1]);
	//check_scene_value(scene);
	display(scene);
	return (EXIT_SUCCESS);
}
