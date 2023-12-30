#ifndef HELPERS_H
# define HELPERS_H

# include <stddef.h>

# define EPSILON (1e-6)
# define OPEN_ERROR (-1)

typedef struct s_vector	t_vector;

/* helpers_math1 */
double		clipping(const double num, const double min, const double max);
double		convert_deg_to_rad(double deg);
double		convert_rad_to_deg(double rad);
t_vector	*convert_coord(t_vector *v_coord, int w, int h);

/* wrapper */
char    	**x_ft_split(char const *str, const char *charset);
char	    *x_get_next_line(int fd);
void	    *x_malloc(const size_t size);
int		    x_open(const char *path, int open_flag);

#endif
