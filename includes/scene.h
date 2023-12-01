#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "camera.h"
# include "light.h"
# include "object.h"
# include "result.h"

typedef struct s_deque	t_deque;
typedef enum e_result	t_result;

typedef struct s_scene
{
	t_camera		*camera;
	t_light_ambient	*light_ambient;
	t_light			*light;
	t_sphere		*list_sphere;
}	t_scene;

void	init_scene(t_scene *scene);
void	parse_lines_to_scene(t_deque *lines, t_scene *scene);

#endif