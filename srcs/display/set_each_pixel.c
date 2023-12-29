#include "object.h"
#include "ray.h"
#include "scene.h"

// screen上の点の位置
static t_ray	calc_ray(const int y, const int x, t_scene *scene)
{
	t_ray			ray;
	t_vector		coord_on_screen;
	const t_vector	center_screen = get_center_screen(scene->camera);
	const double	rotation_angle = \
		get_angle(set_axis_base(), scene->camera->dir_norm);

	ray.position = scene->camera->pos;
	coord_on_screen.x = (2.0 * x) / (WIDTH - 1) - 1.0;
	coord_on_screen.y = -(2.0 * HEIGHT / WIDTH * y) / (HEIGHT - 1) + 1.0;
	coord_on_screen.z = 0.0;
	coord_on_screen = \
		rotate_vector_by_quaternion(\
			coord_on_screen, rotation_angle, scene->camera->dir_norm);
	coord_on_screen = vec_add(coord_on_screen, center_screen);
	ray.direction = vec_subtract(coord_on_screen, scene->camera->pos);
	return (ray);
}

static t_rgb	ray_tracing(\
	t_scene *scene, void *nearest_object, const t_ray *ray)
{
	t_intersection	intersection;
	t_material		material;

	//交点の情報を取得
	intersection = get_intersection(scene, nearest_object, ray);
	//lux_totalを環境光で初期化。影にならない場合はlightの明るさもadd
	material.lux_total = get_lux_ambient(scene->light_ambient);
	//影になるか判定。ならない場合のみifに入ってlightの明るさ計算
	if (intersection.l_dot != NOT_ILLUMINATED)
	{
		material.lux_light = \
			get_lux_light(scene->light, nearest_object, intersection.l_dot);
		material.lux_total = \
			get_lux_total(material.lux_total, material.lux_light);
	}
	material.color = (t_rgb){.r = material.lux_total.r * 255, \
		.g = material.lux_total.g * 255, .b = material.lux_total.b * 255};
	return (material.color);
}

void	set_each_pixel_color(\
	t_mlx *mlxs, const int y, const int x, t_scene *scene)
{
	int			color;
	const t_ray	ray = calc_ray(y, x, scene);
	void		*nearest_object;

	nearest_object = NULL;
	if (scene->camera->fov > 0 && scene->camera->fov < 180)
		nearest_object = get_nearest_object(&ray, scene);
	if (nearest_object == NULL)
		color = COLOR_BLUE;
	else
		color = convert_rgb(ray_tracing(scene, nearest_object, &ray));
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
