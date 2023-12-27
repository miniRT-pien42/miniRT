#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdbool.h>

void	*ft_free(void **ptr);
void	*free_2d_array(char ***ptr);
size_t	ft_len_2d_array(const char **array);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_min(const size_t x, const size_t y);
void	ft_putstr_fd(const char *s, int fd);
char	**ft_split(char const *s, const char *charset);
char	*ft_strchr(char *s, int int_c);
bool	ft_strchr_bool(const char *s, int int_c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
bool	ft_streq(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_strlcpy_void(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *s, const size_t maxlen);
size_t	ft_strnlen(const char *s, const size_t maxlen);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

void	*x_malloc(const size_t size);

#endif