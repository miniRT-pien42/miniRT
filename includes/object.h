#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "result.h"
# include "vector.h"

typedef struct s_deque			t_deque;
typedef struct s_intersection	t_intersection;
typedef struct s_ray			t_ray;
typedef struct s_scene			t_scene;

typedef enum s_shape
{
	SPHERE,
	PLANE,
	CYLINDER,
	SHAPE_NONE,
}	t_shape;

typedef struct s_sphere
{
	t_shape		type;
	t_vector	center;
	double		diameter;
	t_rgb		color;
}	t_sphere;

typedef struct s_cylinder {
	t_shape		type;
	t_vector	center;
	t_vector	normal;
	double		diameter;
	double		height;
	t_rgb		color;
}	t_cylinder;

typedef struct s_plane
{
	t_shape		type;
	t_vector	point;
	t_vector	normal;
	t_rgb		color;
}	t_plane;

/* object */
t_shape			get_object_type(void *object);
void			*get_nearest_object(const t_ray	*ray, t_deque *list_object);
t_deque			*init_object(void);
t_result		add_to_list_object(\
	t_deque *list_object, const char **line, const t_shape type);
double			get_distance(const t_ray *ray, void *object);

/* distance */
void			calc_distance_by_discriminant(\
	const double a, const double b, const double d, double *distance);
bool			has_negative_distance(double *distances);

/* intersection */
bool			is_shadow_intersection(\
	t_scene *scene, void *object, const t_ray *ray_shadow);
t_intersection	get_intersection(\
	t_scene *scene, void *nearest_object, const t_ray *ray);

/* sphere/sphere */
t_sphere		*init_sphere(const char **line, t_result *result);

/* sphere/sphere_ray */
double			calc_discriminant_for_sphere(\
	const t_ray *ray, const t_sphere *sphere, double *distances);

/* sphere/sphere_color */
t_vector		get_normal_on_sphere(\
	t_intersection intersection, const t_ray *ray);

/* sphere/sphere_distance */
double			get_distance_to_sphere(const t_ray *ray, t_sphere *sphere);

/* plane/plane */
t_plane			*init_plane(const char **line, t_result *result);

/* plane/plane_ray */
double			get_distance_to_plane(const t_ray *ray, t_plane *plane);

/* sphere/plane_color */
t_vector		get_normal_on_plane(t_plane *plane, const t_ray *ray);

/* cylinder/cylinder */
t_cylinder		*init_cylinder(const char **line, t_result *result);

/* cylinder/cylinder_discriminant */
double			calc_discriminant_for_cylinder(\
	const t_ray *ray, t_cylinder *cylinder, double *distances);

/* cylinder/cylinder_ray */
bool			is_intersect_cylinder(\
	const t_ray *ray, const t_cylinder *cylinder, double distance);
double			get_distance_to_cylinder(\
	const t_ray *ray, t_cylinder *cylinder);

/* cylinder/cylinder_color */
bool			is_cylinder_self_shadow(\
	t_cylinder *cylinder, const t_ray *ray_shadow);
bool			is_inside_cylinder(\
	const t_cylinder *cylinder, const t_ray *ray_shadow);
t_vector		get_normal_on_cylinder(\
	t_intersection intersection, const t_ray *ray);

#endif
