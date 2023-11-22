#ifndef OBJECT_H
# define OBJECT_H

# include <stdbool.h>
# include "vector.h"
# include "color.h"

typedef struct s_sphere	t_sphere;
typedef struct s_scene	t_scene;

typedef struct s_sphere
{
	t_vector	center;
	double		diameter;
	t_rgb		color;
	t_sphere	*next;
}	t_sphere;

t_sphere	*init_sphere(char *line);
bool		is_intersect_to_sphere(const int y, const int x, t_scene *scene);

#endif
