#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "ft_deque.h"
# include "vector.h"

typedef struct s_sphere			t_sphere;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_intersection	t_intersection;
typedef struct s_ray			t_ray;

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

// object/object.c
t_shape			get_object_type(void *object);
void			*get_nearest_object(t_vector ray, t_scene *scene);
t_deque			*init_object(void);
void			add_to_list_object(\
	t_deque *list_object, const char **line, const t_shape type);
double			get_distance(t_vector ray, t_vector pos, void *object);

// object/distance.c
void			calc_distance_by_discriminant(\
	const double a, const double b, const double d, double *distance);
double			get_closer_distance(double discriminant, double *distance);

// sphere/sphere.c
t_sphere		*init_sphere(const char **line);

// sphere/sphere_ray.c
double			calc_discriminant_for_sphere(\
	t_vector ray, const t_sphere *sphere, t_vector pos, double *distances);
double			get_distance_to_sphere(\
	t_vector ray, t_vector pos, t_sphere *sphere);

// sphere/sphere_color.c
t_vector		get_normal_on_sphere(\
	t_scene *scene, t_intersection intersection, t_vector ray);

// plane/plane.c
t_plane			*init_plane(const char **line);

// plane/plane_ray.c
double			get_distance_to_plane(\
	t_vector ray, t_vector pos, t_plane *plane);

// cylinder/cylinder.c
t_cylinder		*init_cylinder(const char **line);

// cylinder/cylinder_ray.c
double			calc_discriminant_for_cylinder(\
	t_ray *ray, t_cylinder *cylinder, double *distances);
bool			is_intersect_cylinder(\
	t_ray *ray, const t_cylinder *cylinder, double distance);
double			get_distance_to_cylinder(\
	t_vector ray_direction, t_vector pos, t_cylinder *cylinder);

// cylinder/cylinder_color.c
t_vector	get_normal_on_cylinder(\
	t_scene *scene, t_intersection intersection, t_vector ray);

#endif
