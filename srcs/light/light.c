#include <stdlib.h>
#include "light.h"
#include "value_tmp.h"

t_light_ambient	*init_light_ambient(void)
{
	t_light_ambient	*light_ambient;

	light_ambient = (t_light_ambient *)malloc(sizeof(t_light_ambient));
	if (light_ambient == NULL)
		return (NULL);
	light_ambient->bright = LIGHT_A_BRIGHT;
	light_ambient->color = (t_rgb)LIGHT_A_COLOR;
	return (light_ambient);
}

t_light	*init_light(void)
{
	t_light	*light;
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		return (NULL);
	light->pos = (t_vector)LIGHT_POS;
	light->bright = LIGHT_BRIGHT;
	return (light);
}
