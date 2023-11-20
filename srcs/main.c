
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/scene.h"
#include "../include/ray.h"
#include "../include/vector.h"
#include "display.h"

#define WIDTH 512
#define HEIGHT 512

//todo: 実際にはコマンドライン引数に指定したRTファイルをparseしてsceneを初期化する
int	main(int argc, char **argv) {
	t_scene *scene;
	t_ray ray;
	t_ray ray_shadow;

	(void) argc;
	scene = init_scene(argv[1]);

	display();
	return (EXIT_SUCCESS);
}
