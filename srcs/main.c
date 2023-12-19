#include "debug.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

static bool	is_valid_argc(const int argc)
{
	return (argc == 2);
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
		error_exit(ERR_ARGS);
	if (!is_valid_file_path(argv[1]))
		error_exit(ERR_FILEPATH);
	scene = parse(argv[1]);
	if (!is_valid_scene_value(&scene))
	{
		// todo: put error
		return (EXIT_FAILURE);
	}
	display(&scene);
	return (EXIT_SUCCESS);
}
