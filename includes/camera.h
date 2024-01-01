#ifndef CAMERA_H
# define CAMERA_H

# include "result.h"
# include "vector.h"

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir_norm;
	int			fov;
}	t_camera;

/* camera */
t_camera	*init_camera(const char **line, t_result *result);

#endif
