#include "color.h"
#include "libft.h"
#include "parse.h"

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
