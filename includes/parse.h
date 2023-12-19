#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include <vector.h>

# define OPEN_ERROR		(-1)
# define FILE_EXTENSION	".rt"

typedef struct s_scene	t_scene;
typedef struct s_rgb	t_rgb;
typedef enum e_result	t_result;
typedef struct s_deque	t_deque;

/* parse */
t_result	parse(const char *file_name, t_scene *scene);
void		del_lines(void *args);

/* convert */
t_vector	convert_line_to_vector(const char *line, const char delimiter);
t_rgb		convert_line_to_rgb(const char *line, const char delimiter);

/* validation */
bool		is_valid_file_path(const char *filepath);
size_t		calc_length_of_2d_array(const char **array);
bool		is_correct_number_of_blocks(const t_deque *lines);
bool		is_valid_lines(t_deque **lines);
bool		is_valid_scene_value(const t_scene *scene);

#endif
