#include "libft.h"
#include "parse.h"
#include "result.h"
#include "vector.h"

double	convert_to_double(const char *s, t_result *result)
{
	double		num;
	const char	*end_ptr;

	num = ft_strtod(s, &end_ptr);
	if (end_ptr == NULL)
		*result = FAILURE;
	return (num);
}

double	convert_to_double_in_range(\
			const char *s, const double min, const double max, t_result *result)
{
	double	num;

	num = convert_to_double(s, result);
	if (*result == FAILURE)
		return (UNUSED);
	if (min <= num && num <= max)
		return (num);
	*result = FAILURE;
	return (UNUSED);
}

t_vector	convert_line_to_vector(const char *line, t_result *result)
{
	t_vector	vec;
	char		**strs;

	strs = ft_split(line, DELIMITER_VALUE_STR);
	vec.x = convert_to_double(strs[0], result);
	vec.y = convert_to_double(strs[1], result);
	vec.z = convert_to_double(strs[2], result);
	free_2d_array(&strs);
	return (vec);
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
