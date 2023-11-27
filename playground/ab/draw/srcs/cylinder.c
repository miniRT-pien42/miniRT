#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "color.h"
#include "display.h"
#include "object.h"
#include "utils.h"
#include "vector.h"

// 円柱の中心座標ベクトル、円柱の軸方向(法線ベクトル), 半径、高さ
const t_cylinder cylinder = {{0, -1, 10}, {0, 1, 0}, 1.0, 3.0};

typedef struct s_discriminant {
	double	a;
	double	b;
	double	c;
	double	d;
}	t_discriminant;

// 中心軸上での交差判定
static t_discriminant	calc_discriminant(const t_ray *ray)
{
	t_discriminant	discriminant;
    double			a;
	double			b;
    double			c;

	a = vec_norm(vec_cross(ray->direction, cylinder.axis_normal));
	a *= a;
	b = 2 * vec_dot(vec_cross(ray->direction, cylinder.axis_normal), \
					vec_cross(vec_subtract(ray->position, cylinder.center), cylinder.axis_normal));
	c = vec_norm(vec_cross(vec_subtract(ray->position, cylinder.center), cylinder.axis_normal));
	c = pow(c, 2) - pow(cylinder.r, 2);
	discriminant.a = a;
	discriminant.b = b;
	discriminant.c = c;
	discriminant.d = b * b - 4 * a * c;
	return (discriminant);
}

static bool	is_intersect_cylinder(const t_ray *ray)
{
    const t_discriminant	discriminant = calc_discriminant(ray);
	double 					t;
	double 					t1;
	double 					t2;

    // 交差しない
    if (discriminant.d < 0) {
        return (false);
    }

	if (discriminant.d == 0)
		t = -discriminant.b / (2 * discriminant.a);
	else
	{
		// rayとcylinderの距離(円柱の内側と外側)
		t1 = (-discriminant.b - sqrt(discriminant.d)) / (2 * discriminant.a);
		t2 = (-discriminant.b + sqrt(discriminant.d)) / (2 * discriminant.a);
		t = (t1 > 0 && t2 > 0) ? fmin(t1, t2) : fmax(t1, t2);
	}

	if (t > 0)
	{
		// 交点位置pa
		const t_vector	pa = vec_add(ray->position, vec_scalar(ray->direction, t));
		// paからの法線ベクトル
		const t_vector	pa_normal = vec_subtract(pa, cylinder.center);
		// 中心軸上での法線とpaから求めた法線が同じ方向を向いていてheight以内かどうか
		const double	height = vec_dot(cylinder.axis_normal, pa_normal);
		if (0 <= height && height <= cylinder.height)
			return (true);
	}
    // 交差しない
    return (false);
}

static int	calc_cylinder_color(const t_ray *ray)
{
	int	color;

    if (is_intersect_cylinder(ray))
		color = COLOR_PINK;
	else
		color = COLOR_BLUE;
    return (color);
}

void	set_each_cylinder_pixel_color(t_mlx *mlxs, const int y, const int x)
{
	const t_ray	ray = calc_ray(y, x);
	const int	color = calc_cylinder_color(&ray);

	printf("RGB=(%d,%d,%d)\n", color, color, color);
	my_mlx_pixel_put(mlxs->image, y, x, color);
}
