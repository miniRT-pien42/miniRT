#ifndef HELPERS_H
# define HELPERS_H

# define EPSILON (1e-6)

typedef struct s_vector	t_vector;

double		clipping(const double num, const double min, const double max);
double		convert_deg_to_rad(double deg);
double		convert_rad_to_deg(double rad);
t_vector	*convert_coord(t_vector *v_coord, int w, int h);

#endif
