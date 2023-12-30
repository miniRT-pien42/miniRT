#ifndef QUATERNION_H
# define QUATERNION_H

typedef struct s_quaternion {
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quaternion;

/* quaternion */
t_quaternion	get_rotate_quaternion(t_vector axis, double angle);
t_vector		rotate_vector_by_quaternion(\
	t_vector dir_norm, t_vector v, t_screen_info screen);
#endif