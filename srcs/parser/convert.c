#include "color.h"
#include "libft.h"
#include "parse.h"
#include "vector.h"
#include <stdlib.h> // todo: rm (atof)

t_vector	convert_line_to_vector(const char *line)
{
	t_vector	vec;
	char		**strs;

	strs = ft_split(line, DELIMITER_VALUE_STR);
	vec = \
		(t_vector){.x = atof(strs[0]), .y = atof(strs[1]), .z = atof(strs[2])};
	free_2d_array(&strs);
	return (vec);
}

t_rgb	convert_line_to_rgb(const char *line, t_result *result)
{
	t_rgb	rgb;
	char	**strs;

	strs = ft_split(line, DELIMITER_VALUE_STR);
	rgb.r = convert_to_uint8_in_range(strs[0], RGB_MIN, RGB_MAX, result);
	rgb.g = convert_to_uint8_in_range(strs[1], RGB_MIN, RGB_MAX, result);
	rgb.b = convert_to_uint8_in_range(strs[2], RGB_MIN, RGB_MAX, result);
	free_2d_array(&strs);
	return (rgb);
}
