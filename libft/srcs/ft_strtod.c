#include "libft.h"
#include <stdbool.h>
#include <stdint.h>

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

static void	convert_decimal_part(double *num, \
	const char **s, bool *is_valid_num, const unsigned int decimal_precision)
{
	double			inverse_power;
	unsigned int	digits_of_decimal;

	inverse_power = 0.1;
	digits_of_decimal = 0;
	while (ft_isdigit(**s) && digits_of_decimal < decimal_precision)
	{
		*is_valid_num = true;
		*num += inverse_power * (**s - '0');
		inverse_power /= 10;
		digits_of_decimal++;
		(*s)++;
	}
	while (**s)
	{
		if (!ft_isdigit(**s))
		{
			*is_valid_num = false;
			return ;
		}
		(*s)++;
	}
}

static const char	*set_end_ptr(bool is_valid_num, const char *s)
{
	if (is_valid_num && *s == '\0')
		return (s);
	return (NULL);
}

double	ft_strtod(\
	const char *s, const char **end_ptr, const unsigned int decimal_precision)
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
		convert_decimal_part(&num, &s, &is_valid_num, decimal_precision);
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

	// decimal_precision = 10 for miniRT
	num = ft_strtod(s, &end_ptr, 10);
	// valid
	if (end_ptr != NULL)
	{
		printf("num    : [%.10f]\n", num);
		printf("expect : [%.10f]\n", expect);
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
	// error
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
	run_ft_strtod("    1.23456789123456789", 0);
	run_ft_strtod("1.23456789123456789   ", 0);
	run_ft_strtod("    1.23456789123456789   ", 0);
	run_ft_strtod("1.23456789123456789xxx", 0);

	// valid
	run_ft_strtod("123", 123);
	run_ft_strtod("-123", -123);
	run_ft_strtod("2147483647", 2147483647);
	run_ft_strtod("2147483648", 2147483648);
	run_ft_strtod("-2147483648", -2147483648);
	run_ft_strtod("-2147483649", -2147483649);
	// just 10 digits
	run_ft_strtod("123.0123456789", 123.0123456789);
	run_ft_strtod("-123.0123456789", -123.0123456789);
	// 11 digits
	run_ft_strtod("123.01234567891", 123.0123456789);
	run_ft_strtod("-123.01234567891", -123.0123456789);
	run_ft_strtod("123.01234567897", 123.0123456789);
	run_ft_strtod("-123.01234567897", -123.0123456789);
	// more
	run_ft_strtod("1.23456789123456789", 1.2345678912);
	run_ft_strtod("-1.23456789123456789", -1.2345678912);
}
*/
