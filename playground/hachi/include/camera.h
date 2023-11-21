#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>
# include "./vector.h"
# include "./ray.h"

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir_n; //正規化済みの視線方向ベクトル
	int	fov; //doubleかもしれない
}	t_camera;

#endif //CAMERA_H
