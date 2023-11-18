#ifndef SCENE_H
# define SCENE_H

# include <math.h>
# include "vector.h"
//# include "ray.h"
# include "light.h"
# include "primitive.h"

typedef struct s_scene
{
	t_vec3			eye_pos;
	t_light_ambient	*light_ambient;
	t_light			*lights;
	t_primitive		*list_primitive;
}	t_scene;

#endif //SCENE_H
