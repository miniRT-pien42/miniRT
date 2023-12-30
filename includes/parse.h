#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include <stdint.h>
# include "result.h"

# define FILE_EXTENSION			".rt"
# define AT_LEAST_LINES			3
# define DELIMITER_WHITE_SPACE	" \f\n\r\t\v"
# define DELIMITER_VALUE_STR	","
# define DELIMITER_VALUE_CHAR	','

# define ELEM_COUNT_AMBIENT		3
# define ELEM_COUNT_CAMERA		4
# define ELEM_COUNT_LIGHT		4
# define ELEM_COUNT_PLANE		4
# define ELEM_COUNT_SPHERE		4
# define ELEM_COUNT_CYLINDER	6

# define UNUSED		0
# define RGB_MIN	0
# define RGB_MAX	255
# define FOV_MIN	0
# define FOV_MAX	180
# define RATIO_MIN	(0.0)
# define RATIO_MAX	(1.0)
# define DIR_N_MIN	(-1.0)
# define DIR_N_MAX	(1.0)
# define VALID_NORMAL_LEN_MIN	(0.99)
# define VALID_NORMAL_LEN_MAX	(1.01)

typedef struct s_scene	t_scene;
typedef struct s_rgb	t_rgb;
typedef struct s_deque	t_deque;
typedef struct s_vector	t_vector;

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

/* convert to uint8_t */
uint8_t			convert_to_uint8_in_range(\
				const char *s, const int min, const int max, t_result *result);
t_rgb			convert_line_to_rgb(const char *line, t_result *result);

/* convert to double */
double			convert_to_double(const char *s, t_result *result);
double			convert_to_double_in_range(\
		const char *s, const double min, const double max, t_result *result);
t_vector		convert_line_to_vector_in_range(\
		const char *line, const double min, const double max, t_result *result);
t_vector		convert_line_to_vector(const char *line, t_result *result);
t_vector		init_normal_vector(\
		const char *line, const double min, const double max, t_result *result);

/* validation */
bool			is_valid_file_path(const char *filepath);
bool			starts_with_valid_identifier(t_deque *lines);
void			split_lines(t_deque *lines);
bool			is_valid_lines(t_deque **lines);
t_identifier	set_identifier(const char *head_line);
bool			is_correct_number_of_blocks(const t_deque *lines);
bool			is_correct_value_counts(const t_deque *lines);
bool			is_scene_value_unique(const t_deque *lines);

#endif
