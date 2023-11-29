#include "scene.h"

void	init_scene(t_scene *scene)
{
	//todo: #3 argv経由で渡されたRTファイルをparseして初期化（行先頭の型識別子に対応したinitを呼び出す)
	scene->camera = init_camera();
	scene->light_ambient = init_light_ambient();
	scene->light = init_light();
	scene->list_sphere = init_sphere();
}
