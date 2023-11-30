#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "camera.h"
# include "light.h"
# include "object.h"
# include "ft_deque.h"

typedef struct s_scene
{
	t_camera		*camera;
	t_light_ambient	*light_ambient;
	t_light			*light;
	t_deque			*list_object;
}	t_scene;

t_scene	*init_scene(char *rt_file);

#endif