#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	vec_add(const t_vector a, const t_vector b);
t_vector	vec_subtract(const t_vector a, const t_vector b);
double		vec_dot(const t_vector a, const t_vector b);
t_vector	vec_cross(const t_vector a, const t_vector b);
t_vector	vec_scalar(const t_vector v, double scalar);
t_vector	vec_normalize(const t_vector v);
double		vec_length(const t_vector v);
double		vec_angle(const t_vector v1, const t_vector v2);
bool		is_vector_opposite(t_vector a, t_vector b);

#endif
