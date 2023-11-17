#ifndef MATERIAL_H
# define MATERIAL_H

# include <math.h>
# include "./vector.h"
# include "./ray.h"

typedef struct s_material
{
	double	k_a; //環境光反射係数
	t_rgb	color;//k_d
}	t_material;


#endif //MATERIAL_H
