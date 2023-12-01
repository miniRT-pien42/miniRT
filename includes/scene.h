#ifndef SCENE_H
# define SCENE_H

# define AXIS_BASE_X	0.0
# define AXIS_BASE_Y	0.0
# define AXIS_BASE_Z	1.0

# include "camera.h"
# include "light.h"
# include "object.h"

typedef struct s_deque	t_deque;

typedef struct s_scene
{
	t_camera		*camera;
	t_light_ambient	*light_ambient;
	t_light			*light;
	t_deque			*list_object;
	t_vector		center_screen;
	double			rotation_angle;
}	t_scene;

void		init_scene(t_scene *scene);
void		parse_lines_to_scene(t_deque *lines, t_scene *scene);
t_vector	set_axis_base(void);

#endif