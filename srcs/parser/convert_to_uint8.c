#include "libft.h"
#include "parse.h"
#include "result.h"

// min: 0 ~ 255, max: 0 ~ 255
uint8_t	convert_to_uint8_in_range(const char *s, const int min, const int max, t_result *result)
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
