#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir_n; //正規化済みの視線方向ベクトル
	int			fov; //doubleかもしれない
}	t_camera;

t_camera	*init_camera(char *line);

#endif
