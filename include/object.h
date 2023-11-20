
#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "color.h"

typedef struct s_sphere		t_sphere;

typedef struct s_sphere {
	t_vector	center;
	double		diameter;
	t_rgb		color;
	t_sphere	*next;
}	t_sphere;

#endif
