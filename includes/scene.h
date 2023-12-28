#ifndef SCENE_H
# define SCENE_H

# define AXIS_BASE_X	0.0
# define AXIS_BASE_Y	0.0
# define AXIS_BASE_Z	1.0

# define TYPE_AMBIENT	"A"
# define TYPE_CAMERA	"C"
# define TYPE_LIGHT		"L"
# define TYPE_PLANE		"pl"
# define TYPE_SPHERE	"sp"
# define TYPE_CYLINDER	"cy"

# include "camera.h"
# include "light.h"

typedef struct s_deque	t_deque;

typedef struct s_scene
{
	t_camera		*camera;
	t_light_ambient	*light_ambient;
	t_light			*light;
	t_deque			*list_object;
}	t_scene;

void		init_scene(t_scene *scene);
t_result	parse_lines_to_scene(t_deque *lines, t_scene *scene);
t_vector	set_axis_base(void);
void		destroy_scene(t_scene *scene);

#endif