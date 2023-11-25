#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	vec_add(const t_vector a, const t_vector b);
t_vector	vec_subtract(const t_vector a, const t_vector b);
t_vector	vec_cross(const t_vector a, const t_vector b);
double		vec_dot(const t_vector a, const t_vector b);
t_vector	vec_scalar(const t_vector v, double scalar);
double		get_scalar(const t_vector v);
t_vector	vec_normalize(const t_vector v);

#endif
