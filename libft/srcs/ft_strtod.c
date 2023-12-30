#include "libft.h"
#include <stdbool.h>

static bool	is_sign(const int c)
{
	return (c == '-' || c == '+');
}

static double	set_sign(const char **s)
{
	const char	c = **s;

	if (is_sign(c))
	{
		(*s)++;
		if (c == '-')
			return (-1.0);
	}
	return (1.0);
}

static void	convert_decimal_part(\
								double *num, const char **s, bool *is_valid_num)
{
	double	inverse_power;

	inverse_power = 0.1;
	while (ft_isdigit(**s))
	{
		*is_valid_num = true;
		*num += inverse_power * (**s - '0');
		inverse_power /= 10;
		(*s)++;
	}
}

static const char	*set_end_ptr(bool is_valid_num, const char *s)
{
	if (is_valid_num && *s == '\0')
		return (s);
	return (NULL);
}

double	ft_strtod(const char *s, const char **end_ptr)
{
	double			num;
	bool			is_valid_num;
	const double	sign = set_sign(&s);

	num = 0;
	is_valid_num = false;
	while (ft_isdigit(*s))
	{
		is_valid_num = true;
		num = num * 10 + *s - '0';
		s++;
	}
	if (*s == '.' && is_valid_num)
	{
		is_valid_num = false;
		s++;
		convert_decimal_part(&num, &s, &is_valid_num);
	}
	*end_ptr = set_end_ptr(is_valid_num, s);
	return (num * sign);
}

/*
#include <assert.h>
#include <stdio.h>

static void	run_ft_strtod(char *s, double expect)
{
	const char	*end_ptr;
	double		num;

	num = ft_strtod(s, &end_ptr);
	// valid
	if (end_ptr != NULL)
	{
		printf("num    : [%.20f]\n", num);
		printf("expect : [%.20f]\n", expect);
		printf("\n");
		assert(num == expect);
		return ;
	}
	// error
	printf("error  : [%s]\n", s);
	printf("\n");
}

int main(void)
{
	run_ft_strtod("", 0);
	run_ft_strtod("   ", 0);
	run_ft_strtod(".", 0);
	run_ft_strtod(".123", 0);
	run_ft_strtod("   .123", 0);
	run_ft_strtod("12   .345", 0);
	run_ft_strtod("123.", 0);
	run_ft_strtod("+-123", 0);
	run_ft_strtod("-+123", 0);
	run_ft_strtod("--123", 0);
	run_ft_strtod("++123", 0);
	run_ft_strtod("  123", 0);
	run_ft_strtod("123   ", 0);
	run_ft_strtod("a123", 0);
	run_ft_strtod("123a", 0);

	run_ft_strtod("123", 123);
	run_ft_strtod("-123", -123);
	run_ft_strtod("2147483647", 2147483647);
	run_ft_strtod("2147483648", 2147483648);
	run_ft_strtod("-2147483648", -2147483648);
	run_ft_strtod("-2147483649", -2147483649);
	run_ft_strtod("1.23456789123456789", 1.23456789123456789);
	run_ft_strtod("-1.23456789123456789", -1.23456789123456789);
}
*/
