#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include <vector.h>

# define OPEN_ERROR		(-1)
# define FILE_EXTENSION	".rt"
# define AT_LEAST_LINES	3

# define ELEM_COUNT_AMBIENT		3
# define ELEM_COUNT_CAMERA		4
# define ELEM_COUNT_LIGHT		4
# define ELEM_COUNT_PLANE		4
# define ELEM_COUNT_SPHERE		4
# define ELEM_COUNT_CYLINDER	6

typedef struct s_scene	t_scene;
typedef struct s_rgb	t_rgb;
typedef enum e_result	t_result;
typedef struct s_deque	t_deque;

typedef enum e_identifier
{
	ID_AMBIENT = 0,
	ID_CAMERA = 1,
	ID_LIGHT = 2,
	ID_PLANE = 3,
	ID_SPHERE = 4,
	ID_CYLINDER = 5,
	ID_OTHER = 6,
}	t_identifier;

/* parse */
t_result		parse(const char *file_name, t_scene *scene);
void			del_lines(void *args);
t_deque			*read_file(const char *file_name);

/* convert */
t_vector		convert_line_to_vector(const char *line, const char delimiter);
t_rgb			convert_line_to_rgb(const char *line, const char delimiter);

/* validation */
bool			is_valid_file_path(const char *filepath);
bool			starts_with_valid_identifier(t_deque *lines);
void			split_line_with_space(t_deque *lines);
bool			is_valid_lines(t_deque **lines);
t_identifier	set_identifier(const char *head_line);
bool			is_correct_number_of_blocks(const t_deque *lines);
bool			is_correct_value_counts(const t_deque *lines);
bool			is_valid_scene_value(const t_scene *scene);
bool			is_scene_value_unique(const t_deque *lines);

#endif
