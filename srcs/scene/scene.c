
#include <stdlib.h>
#include "scene.h"

t_scene	*init_scene(char *rt_file)
{
	t_scene			*scene;
//	t_camera		camera;
//	t_light_ambient	light_ambient;
//	t_light			light;
//	t_sphere		*sphere1;
//	t_sphere		*sphere2;
//	t_sphere		*sphere3;

	(void)rt_file;
	scene = (t_scene *)malloc(sizeof(t_scene));
	//todo: #3 argv経由で渡されたRTファイルをparseして初期化
	//todo: #13 とりあえずの動作確認用に固定値で初期化
	return (scene);
}
