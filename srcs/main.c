#include "display.h"
#include "error.h"
#include "parse.h"
#include "scene.h"
#include <stdlib.h>

static bool	is_valid_argc(const int argc)
{
	return (argc == 2);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_result	result;

	if (!is_valid_argc(argc))
		error_exit(ERR_ARGS);
	if (!is_valid_file_path(argv[1]))
		error_exit(ERR_FILEPATH);
	result = parse(argv[1], &scene);
	if (result == FAILURE)
		error_exit(ERR_RTFILE);
	display(&scene);
	return (EXIT_SUCCESS);
}
