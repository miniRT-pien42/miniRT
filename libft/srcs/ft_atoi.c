#include "libft.h"
#include <limits.h>

static bool	is_sign(const int c)
{
	return (c == '-' || c == '+');
}

static int	set_sign(const char **s)
{
	const char	c = **s;

	if (is_sign(c))
	{
		(*s)++;
		if (c == '-')
			return (-1);
	}
	return (1);
}

static bool	is_leading_zeros(const char *head, const char *str, const int num)
{
	if (num != 0)
		return (false);
	if (head == str)
		return (false);
	if (*str != '0')
		return (false);
	if (is_sign(*(str - 1)))
		return (false);
	return (true);
}

static bool	is_overflow(int *num, const int c, const int sign)
{
	int	max_div;
	int	max_mod;

	max_div = INT_MAX / 10;
	max_mod = INT_MAX % 10 + (sign == -1);
	if (*num > max_div)
	{
		*num = 0;
		return (true);
	}
	if (*num == max_div && c - '0' > max_mod)
	{
		*num = 0;
		return (true);
	}
	return (false);
}

bool	ft_atoi(const char *str, int *num)
{
	const char	*head = str;
	bool		at_least_one_digit;
	const int	sign = set_sign(&str);

	*num = 0;
	at_least_one_digit = false;
	while (ft_isdigit(*str))
	{
		at_least_one_digit = true;
		if (is_leading_zeros(head, str, *num))
			return (false);
		if (is_overflow(num, *str, sign))
			return (false);
		*num = *num * 10 + *str - '0';
		str++;
	}
	if (*str || !at_least_one_digit)
		return (false);
	*num *= sign;
	return (true);
}

/*
#include <stdbool.h>
#include <assert.h>

int	main(void)
{
	int	num;

	assert(ft_atoi("   ", &num) == false);
	assert(ft_atoi("-", &num) == false);
	assert(ft_atoi("+", &num) == false);
	assert(ft_atoi("a", &num) == false);
	assert(ft_atoi("a1", &num) == false);
	assert(ft_atoi("1   ", &num) == false);
	assert(ft_atoi("1a", &num) == false);
	assert(ft_atoi("   1", &num) == false);
	assert(ft_atoi("--1", &num) == false);
	assert(ft_atoi("++2", &num) == false);
	assert(ft_atoi("+-3", &num) == false);
	assert(ft_atoi("+001", &num) == false);
	assert(ft_atoi("0-1", &num) == false);
	assert(ft_atoi("2147483648", &num) == false);
	assert(ft_atoi("-2147483649", &num) == false);
	assert(ft_atoi("000", &num) == false);
	assert(ft_atoi("0011", &num) == false);
	assert(ft_atoi("0.0123", &num) == false);

	assert(ft_atoi("-0", &num) == true);
	assert(ft_atoi("+0", &num) == true);
	assert(ft_atoi("+1", &num) == true);
	assert(ft_atoi("-1", &num) == true);
	assert(ft_atoi("0", &num) == true);
	assert(ft_atoi("1234", &num) == true);
	assert(ft_atoi("-1234", &num) == true);
	assert(ft_atoi("2147483647", &num) == true);
	assert(ft_atoi("-2147483648", &num) == true);
}
*/
