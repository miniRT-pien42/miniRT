#include <stdio.h>
#include <stdlib.h>
#include "scene.h"
#include "libft.h"

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

static char	**read_file(const char *file_name)
{
	(void)file_name;
	return (NULL);
}

static void	parse_lines(const char **lines, t_scene *scene)
{
	(void)lines;
	(void)scene;
	return ;
}

t_scene	parse(const char *file_name)
{
	t_scene	scene;
	char	**lines;

	lines = read_file(file_name);
	init_scene(&scene);
	parse_lines((const char **)lines, &scene);
	free_2d_array(&lines);
	return (scene);
}

