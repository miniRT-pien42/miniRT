#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdbool.h>

void	*ft_free(void **ptr);
void	*free_2d_array(char ***ptr);

char	**ft_split(char const *s, char c);
int 	ft_strcmp(const char *s1, const char *s2);
bool	ft_streq(const char *s1, const char *s2);
void	ft_strlcpy_void(char *dst, const char *src, size_t dstsize);
char	*ft_strndup(const char *s, const size_t maxlen);
size_t	ft_strnlen(const char *s, const size_t maxlen);

void	*x_malloc(const size_t size);

#endif