
#include <stdlib.h>
#include "../../include/scene.h"

t_scene	*init_scene(char *rt_file)
{
	t_scene			*scene;
	t_camera		camera;
	t_light_ambient	light_ambient;
	t_light			light;
	t_sphere		*sphere1;
	t_sphere		*sphere2;
	t_sphere		*sphere3;

	(void)rt_file;
	scene = (t_scene *)malloc(sizeof(t_scene));
	//todo: scene各メンバ初期化
	return (scene);
}