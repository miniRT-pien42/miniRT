#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "light.h"
# include "object.h"

typedef struct s_scene
{
	t_camera		*camera;
	t_light_ambient	*light_ambient;
	t_light			*light;
	t_sphere		*list_sphere;
	t_vector		center_screen;
	double			rotation_angle;
}	t_scene;

t_scene	*init_scene(char *rt_file);

#endif