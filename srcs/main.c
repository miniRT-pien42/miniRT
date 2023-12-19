#include "debug.h"
#include "display.h"
#include "parse.h"
#include "scene.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool	is_valid_argc(const int argc)
{
	return (argc == 2);
}

// todo: validate .rt file
static bool	is_valid_file_path(const char *filepath)
{
	printf("filepath: %s\n", filepath);
	return (true);
}

// todo: validate scene value
static bool	is_valid_scene_value(const t_scene *scene)
{
	debug_print_scene_value(scene);
	return (true);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (!is_valid_argc(argc))
	{
		// todo: put error
		return (EXIT_FAILURE);
	}
	if (!is_valid_file_path(argv[1]))
	{
		// todo: put error
		return (EXIT_FAILURE);
	}
	scene = parse(argv[1]);
	if (!is_valid_scene_value(&scene))
	{
		// todo: put error
		return (EXIT_FAILURE);
	}
	display(&scene);
	return (EXIT_SUCCESS);
}
