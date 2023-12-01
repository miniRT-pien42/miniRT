#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdbool.h>

void	*ft_free(void **ptr);
void	*free_2d_array(char ***ptr);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(char *s, int int_c);
bool	ft_strchr_bool(const char *s, int int_c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
bool	ft_streq(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_strlcpy_void(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strndup(const char *s, const size_t maxlen);
size_t	ft_strnlen(const char *s, const size_t maxlen);

void	*x_malloc(const size_t size);

#endif