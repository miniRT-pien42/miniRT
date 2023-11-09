#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define RED		"\033[31m"
#define WHITE	"\033[97m"
#define END		"\033[0m"

typedef struct s_vector {
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray {
	t_vector	position;  // 位置ベクトル
	t_vector	direction; // 方向ベクトル
}	t_ray;

typedef struct s_sphere {
	t_vector	center;
	double		r;
}	t_sphere;

// 2 つのベクトルの内積
static double	dot(t_vector a, t_vector b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// ベクトルの長さ
// static double	calc_len(t_vector v) {
// 	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
// }

// ベクトルの差 (方向ベクトルを求める)
static t_vector	subtract(t_vector a, t_vector b) {
	t_vector	v = {a.x - b.x,
					a.y - b.y,
					a.z - b.z};

	return (v);
}

// 視点からの ray と球の衝突判定
static bool	is_intersect(t_ray ray, t_sphere sphere) {
	t_vector	v = subtract(ray.position, sphere.center);
	double		a = dot(ray.direction, ray.direction);
	double		b = 2.0 * dot(v, ray.direction);
	double		c = dot(v, v) - sphere.r * sphere.r;
	double		discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}

const int	WIDTH = 30;
const int	HEIGHT = 30;

int	main(void) {
	t_sphere	sphere = {{0, 0, 5}, 1.0};
	t_vector	view = {0, 0, -5};

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			double		screen_x = (2.0 * j) / (WIDTH - 1) - 1.0;
			double		screen_y = 1.0 - (2.0 * i) / (HEIGHT - 1);
			t_vector	ray_direction = {screen_x, screen_y, 5};
			t_ray		ray = {view, ray_direction};

			if (is_intersect(ray, sphere))
				printf(RED"."END);
			else
				printf(WHITE"."END);
			printf(" ");
		}
		printf("\n");
	}
}

/*
gcc sphere_1.c -lm && ./a.out
*/