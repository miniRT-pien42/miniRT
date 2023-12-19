#include "debug.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h> // open

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

static void	add_split_line(t_deque *lines, char **line)
{
	char			**split_line_with_space;
	t_deque_node	*node;

	split_line_with_space = ft_split((const char *)*line, ' ');
	ft_free((void **)line);
	node = deque_node_new((void *)split_line_with_space);
	deque_add_back(lines, node);
}

static t_deque	*read_lines(const int fd)
{
	t_deque		*lines;
	char		*line;
	t_result	result;

	lines = deque_new();
	while (true)
	{
		line = get_next_line(fd, &result); // todo: if result==FAILURE
		if (line == NULL)
			break ;
		add_split_line(lines, &line);
	}
	return (lines);
}

static t_deque	*read_file(const char *file_name)
{
	int		fd;
	t_deque	*lines;

	fd = open(file_name, O_RDONLY); // todo: create x_open with error handle
	lines = read_lines(fd);
	return (lines);
}

static void	del_lines(void *args)
{
	char	**lines;

	lines = (char **)args;
	free_2d_array(&lines);
}

t_scene	parse(const char *file_name)
{
	t_scene	scene;
	t_deque	*lines;
	// t_result	result;

	lines = read_file(file_name);
	debug_deque_print(lines, __func__, (void *)print_2d_array);
	// todo: validation
	init_scene(&scene);
	parse_lines_to_scene(lines, &scene);
	deque_clear_all(&lines, del_lines);
	// if (result == FAILURE)
	// {
	// 	destroy_scene(&scene);
	// 	return (FAILURE);
	// }
	// todo: validation
	return (scene);
}
