#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>

typedef struct s_screen_info	t_screen_info;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_quaternion {
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quaternion;

t_vector		vec_add(const t_vector a, const t_vector b);
t_vector		vec_subtract(const t_vector a, const t_vector b);
double			vec_dot(const t_vector a, const t_vector b);
t_vector		vec_cross(const t_vector a, const t_vector b);
t_vector		vec_scalar(const t_vector v, double scalar);
t_vector		vec_normalize(const t_vector v);
double			get_length(const t_vector v);
double			get_angle(const t_vector v1, const t_vector v2);
t_quaternion	get_rotate_quaternion(t_vector axis, double angle);
t_vector		rotate_vector_by_quaternion(t_vector dir_norm, t_vector v, t_screen_info screen);
bool			is_vector_opposite(t_vector a, t_vector b);
bool			is_vector_parallel(t_vector a, t_vector b);

#endif
