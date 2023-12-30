#include "color.h"
#include "libft.h"
#include "parse.h"
#include "result.h"
#include "vector.h"
#include <stdlib.h> // todo: rm (atof)

// min: 0 ~ 255, max: 0 ~ 255
uint8_t	convert_to_uint8_in_range(\
				const char *s, const int min, const int max, t_result *result)
{
	int		num;
	bool	ret;

	ret = ft_atoi(s, &num);
	if (!ret)
	{
		*result = FAILURE;
		return (UNUSED);
	}
	if (min <= num && num <= max)
		return ((uint8_t)num);
	*result = FAILURE;
	return (UNUSED);
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

// todo: set atof result, rm atof
double	convert_to_double_in_range(\
			const char *s, const double min, const double max, t_result *result)
{
	double	num;
	// bool	ret;

	num = atof(s);
	// if (!ret)
	// {
	// 	*result = FAILURE;
	// 	return (UNUSED);
	// }
	if (min <= num && num <= max)
		return (num);
	*result = FAILURE;
	return (UNUSED);
}

t_vector	convert_line_to_vector_in_range(\
		const char *line, const double min, const double max, t_result *result)
{
	t_vector	vec;
	char		**strs;

	strs = ft_split(line, DELIMITER_VALUE_STR);
	vec.x = convert_to_double_in_range(strs[0], min, max, result);
	vec.y = convert_to_double_in_range(strs[1], min, max, result);
	vec.z = convert_to_double_in_range(strs[2], min, max, result);
	free_2d_array(&strs);
	return (vec);
}

// todo: set atof result, rm atof
t_vector	convert_line_to_vector(const char *line, t_result *result)
{
	t_vector	vec;
	char		**strs;

	(void)result;
	strs = ft_split(line, DELIMITER_VALUE_STR);
	vec = \
		(t_vector){.x = atof(strs[0]), .y = atof(strs[1]), .z = atof(strs[2])};
	free_2d_array(&strs);
	return (vec);
}
