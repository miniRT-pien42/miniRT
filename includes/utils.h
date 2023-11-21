
#ifndef UTILS_H
# define UTILS_H

# include "vector.h"

double		clipping(const double num, const double min, const double max);
double		convert_deg_to_rad(double deg);
double		convert_rad_to_deg(double rad);
t_vector	*convert_pw_coordinate(t_vector *v_co, int w, int h);
double		clamp_f(double num, double min, double max);

#endif
