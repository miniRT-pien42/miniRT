#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "ray.h"
#include "vector.h"
#include "display.h"
#include "debug.h"

int	main(int argc, char **argv)
{
	t_scene		*scene;

	(void) argc;
	scene = init_scene(argv[1]);
	check_scene_value(scene);
	display(scene);
	return (EXIT_SUCCESS);
}
