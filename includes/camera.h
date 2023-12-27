#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

typedef enum e_result	t_result;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir_n;
	int			fov;
}	t_camera;

t_camera	*init_camera(const char **line, t_result *result);
t_vector	get_center_screen(t_camera *camera);

#endif
