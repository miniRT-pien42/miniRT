#include "debug.h"
#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include <fcntl.h> // open
#include <stdlib.h> // free

/*
A   ratio      r,g,b
	[0.0-1.0]  [0-255]

C   x,y,z      nx,ny,nz    fov
	[double]   [-1.0-1.0]  [0-180]

L   x,y,z      raio        (r,g,b)
	[double]   [0.0-1.0]   [0-255]

pl  x,y,z      nx,ny,nz    r,g,b
	[double]   [-1.0-1.0]  [0-255]

sp  x,y,z      diameter    r,g,b
	[double]   [double]    [0-255]

cy  x,y,z      nx,ny,nz    diameter  height    r,g,b
	[double]   [-1.0-1.0]  [double]  [double]  [0-255]

*/

void	del_lines(void *args)
{
	char	**lines;

	lines = (char **)args;
	free_2d_array(&lines);
}

t_result	parse(const char *file_name, t_scene *scene)
{
	t_deque		*lines;
	t_result	result;

	lines = read_file(file_name);
	split_lines(lines);
	if (!is_valid_lines(&lines))
	{
		deque_clear_all(&lines, del_lines);
		return (FAILURE);
	}
	debug_deque_print(lines, __func__, (void *)print_2d_array);
	init_scene(scene);
	result = parse_lines_to_scene(lines, scene);
	if (result == FAILURE)
	{
		destroy_scene(scene);
		return (FAILURE);
	}
	debug_print_scene_value(scene);
	if (!is_valid_scene_value(scene))
	{
		destroy_scene(scene);
		return (FAILURE);
	}
	return (SUCCESS);
}
