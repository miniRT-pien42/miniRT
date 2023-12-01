#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "display.h"
# include "helpers.h"

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir_n;
	int			fov;
}	t_camera;

t_camera	*init_camera(char *line);
t_vector	get_center_screen(t_camera *camera);

#endif
