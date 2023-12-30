#ifndef SCENE_H
# define SCENE_H

# include "result.h"

# define TYPE_AMBIENT	"A"
# define TYPE_CAMERA	"C"
# define TYPE_LIGHT		"L"
# define TYPE_PLANE		"pl"
# define TYPE_SPHERE	"sp"
# define TYPE_CYLINDER	"cy"

typedef struct s_light_ambient	t_light_ambient;
typedef struct s_light			t_light;
typedef struct s_deque			t_deque;
typedef struct s_camera			t_camera;

typedef struct s_scene
{
	t_camera		*camera;
	t_light_ambient	*light_ambient;
	t_light			*light;
	t_deque			*list_object;
}	t_scene;

/* scene */
void		destroy_scene(t_scene *scene);
void		init_scene(t_scene *scene);

/* parser/convert_lines_to_scene */
t_result	parse_lines_to_scene(t_deque *lines, t_scene *scene);

#endif