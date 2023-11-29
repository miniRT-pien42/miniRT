#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "color.h"
#include "display.h"
#include "object.h"
#include "utils.h"
#include "vector.h"
#include "ray.h"

// 円柱の中心座標ベクトル、円柱の軸方向(法線ベクトル), 半径、高さ
const t_cylinder cylinder = {{0, -3, 10}, {0, 1, 0}, 1.0, 3.0};

// 中心軸上での交差判定
static t_discriminant	calc_discriminant(const t_ray *ray)
{
	t_discriminant	discriminant;
    double			a;
	double			b;
    double			c;

	a = vec_norm(cross_product(ray->direction, cylinder.axis_normal));
	a *= a;
	b = 2 * vec_dot(cross_product(ray->direction, cylinder.axis_normal), \
					cross_product(vec_subtract(ray->position, cylinder.center), cylinder.axis_normal));
	c = vec_norm(cross_product(vec_subtract(ray->position, cylinder.center), cylinder.axis_normal));
	c = pow(c, 2) - pow(cylinder.r, 2);
	discriminant.a = a;
	discriminant.b = b;
	discriminant.c = c;
	discriminant.d = b * b - 4 * a * c;
	return (discriminant);
}

bool	is_intersect_cylinder(const t_ray *ray)
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

