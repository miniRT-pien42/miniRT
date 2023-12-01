#ifndef PARSE_H
# define PARSE_H

typedef struct s_scene	t_scene;
typedef struct s_rgb	t_rgb;

/* parse */
t_scene		parse(const char *file_name);
void		del(void *args);

/* convert */
t_vector	convert_line_to_vector(const char *line, const char delimiter);
t_rgb		convert_line_to_rgb(const char *line, const char delimiter);

#endif
