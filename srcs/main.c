
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "ray.h"
#include "vector.h"
#include "display.h"

int	main(int argc, char **argv)
{
	t_scene		*scene;

	(void) argc;
	(void) scene;
	scene = init_scene(argv[1]);
	display(scene);
	return (EXIT_SUCCESS);
}
