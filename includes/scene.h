#ifndef SCENE_H
# define SCENE_H

# define AXIS_BASE_X	0.0
# define AXIS_BASE_Y	0.0
# define AXIS_BASE_Z	1.0

# include "camera.h"
# include "light.h"
# include "object.h"
# include "ft_deque.h"

typedef struct s_sphere	t_sphere;

typedef struct s_scene
{
	t_camera		*camera;
	t_light_ambient	*light_ambient;
	t_light			*light;
	t_deque			*list_object;
	t_vector		center_screen;
	double			rotation_angle;
}	t_scene;

t_vector	set_axis_base(void);
t_scene		*init_scene(char *rt_file);

#endif