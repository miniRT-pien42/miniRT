
#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	init_vec3(double x, double y, double z);
t_vec3	vec_sum(const t_vec3 *v1, const t_vec3 *v2);
t_vec3	vec_div(const t_vec3 *v1, const t_vec3 *v2);
t_vec3	scalar_mul(t_vec3 v, double scalar);
double	dot_product(const t_vec3 *v1, const t_vec3 *v2);
t_vec3	cross_product(const t_vec3 *v1, const t_vec3 *v2);
double	get_scalar(const t_vec3 v);
t_vec3	v_normalize(const t_vec3 v);
double	convert_deg_to_rad(double deg);
double	convert_rad_to_deg(double rad);
t_vec3	*convert_pw_coordinate(t_vec3 *v_co, int w, int h);

#endif /*VECTOR_H*/
