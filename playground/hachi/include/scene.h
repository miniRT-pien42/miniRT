#ifndef SCENE_H
# define SCENE_H

# include <math.h>
# include "./vector.h"
# include "./ray.h"
# include "./light.h"
# include "./primitive.h"

typedef struct s_scene
{
	t_light_ambient	light_ambient;
	t_light			*lights;
	t_plane			*list_plane;
	t_sphere		*list_sphere;
	t_cylinder		*list_cylinder;
}	t_scene;

#endif //SCENE_H
