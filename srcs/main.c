
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "ray.h"
#include "vector.h"
#include "display.h"

#define WIDTH 512
#define HEIGHT 512

//todo: 実際にはコマンドライン引数に指定したRTファイルをparseしてsceneを初期化する
int	main(int argc, char **argv)
{
	t_scene		*scene;

	(void) argc;
	(void) scene;
	scene = init_scene(argv[1]);
	display_img(scene);
	return (EXIT_SUCCESS);
}
