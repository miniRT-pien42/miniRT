#include <stdlib.h>
#include "scene.h"

t_vector	set_axis_base(void)
{
	return ((t_vector){AXIS_BASE_X, AXIS_BASE_Y, AXIS_BASE_Z});
}

t_scene	*init_scene(char *rt_file)
{
	t_scene			*scene;
	char			*line = "";//RTファイル1行分

	//todo: #3 argv経由で渡されたRTファイルをparseして初期化（行先頭の型識別子に対応したinitを呼び出す)
	(void)rt_file;
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		return (NULL);
	scene->camera = init_camera(line);
	scene->light_ambient = init_light_ambient(line);
	scene->light = init_light(line);
	scene->list_object = init_object(line);
	scene->center_screen = get_center_screen(scene->camera);
	scene->rotation_angle = \
		get_angle(set_axis_base(), scene->camera->dir_n);
	return (scene);
}
