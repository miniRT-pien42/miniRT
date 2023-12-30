#ifndef QUATERNION_H
# define QUATERNION_H

typedef struct s_quaternion {
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quaternion;

t_vector	rotate_vector_by_quaternion(\
	t_vector v, double angle, t_vector dir_norm);

#endif