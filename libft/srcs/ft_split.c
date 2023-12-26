#include "libft.h"

static bool	is_delimiter(const char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static size_t	count_words(char const *head, const char *charset)
{
	char const	*left = head;
	char const	*right = head;
	size_t		words;

	words = 0;
	while (*right != '\0')
	{
		while (is_delimiter(*right, charset))
		{
			left++;
			right++;
		}
		while (*right != '\0' && !is_delimiter(*right, charset))
			right++;
		if (left != right)
		{
			words++;
			left = right;
		}
	}
	return (words);
}

static bool	set_split_str(char const *head, const char *charset, char **split_strs)
{
	char const	*left = head;
	char const	*right = head;
	size_t		i;

	i = 0;
	while (*right != '\0')
	{
		while (is_delimiter(*right, charset))
		{
			left++;
			right++;
		}
		while (*right != '\0' && !is_delimiter(*right, charset))
			right++;
		if (left != right)
		{
			split_strs[i] = ft_strndup(left, right - left);
			if (split_strs[i] == NULL)
				return (false);
			i++;
			left = right;
		}
	}
	return (true);
}

char	**ft_split(char const *s, const char *charset)
{
	size_t	len;
	char	**split_strs;

	if (s == NULL)
		return (NULL);
	len = count_words(s, charset);
	split_strs = (char **)x_malloc(sizeof(char *) * (len + 1));
	if (!set_split_str(s, charset, split_strs))
		return (free_2d_array(&split_strs));
	split_strs[len] = NULL;
	return (split_strs);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	str[] = "abc///de/fghijk////";
	const char	charset[] = "/";
	char	**result;
	printf("string : %s  (split = %s )\n", str, charset);
	result = ft_split(str, charset);
	if (result == NULL)
	{
		free(result);
		return (0);
	}
	int	i = 0;
	while (result[i])
	{
		printf("[%s]", result[i]);
		i++;
	}
	printf("\n");
	free_2d_array(&result);

	char	str2[] = "+a+bc///de/++fghij+/k   ++";
	char	charset2[] = "+/";
	char	**result2;
	printf("string : %s  (split = %s )\n", str2, charset2);
	result2 = ft_split(str2, charset2);
	if (result2 == NULL)
	{
		free(result2);
		return (0);
	}
	i = 0;
	while (result2[i])
	{
		printf("[%s]", result2[i]);
		i++;
	}
	printf("\n");
	free_2d_array(&result2);
}
*/
