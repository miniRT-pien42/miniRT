#include "ft_deque.h"
#include "libft.h"
#include "scene.h"

static void	del_object(void *args)
{
	ft_free((void **)&args);
}

void	destroy_scene(t_scene *scene)
{
	ft_free((void **)&scene->camera);
	ft_free((void **)&scene->light_ambient);
	ft_free((void **)&scene->light);
	deque_clear_all(&scene->list_object, del_object);
}

t_vector	set_axis_base(void)
{
	return ((t_vector){.x = AXIS_BASE_X, .y = AXIS_BASE_Y, .z = AXIS_BASE_Z});
}

void	init_scene(t_scene *scene)
{
	scene->camera = NULL;
	scene->light_ambient = NULL;
	scene->light = NULL;
	scene->list_object = deque_new();
}
