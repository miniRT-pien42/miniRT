#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include <vector.h>

# define OPEN_ERROR		(-1)
# define FILE_EXTENSION	".rt"

typedef struct s_scene	t_scene;
typedef struct s_rgb	t_rgb;

/* parse */
t_scene		parse(const char *file_name);

/* convert */
t_vector	convert_line_to_vector(const char *line, const char delimiter);
t_rgb		convert_line_to_rgb(const char *line, const char delimiter);

/* validation */
bool		is_valid_file_path(const char *filepath);

#endif
