#include "libft.h"
#include "vector.h"
#include "color.h"
#include <stdlib.h> // todo: rm (atof)

t_vector	convert_line_to_vector(const char *line, const char delimiter)
{
	t_vector	vec;
	char		**strs;

	strs = ft_split(line, delimiter);
	vec = \
		(t_vector){.x = atof(strs[0]), .y = atof(strs[1]), .z = atof(strs[2])};
	free_2d_array(&strs);
	return (vec);
}

t_rgb	convert_line_to_rgb(const char *line, const char delimiter)
{
	t_rgb	rgb;
	char	**strs;

	strs = ft_split(line, delimiter);
	rgb = (t_rgb){.r = atof(strs[0]), .g = atof(strs[1]), .b = atof(strs[2])};
	free_2d_array(&strs);
	return (rgb);
}