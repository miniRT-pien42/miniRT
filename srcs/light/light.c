#include <stdlib.h>
#include "light.h"

t_light_ambient	*init_light_ambient(char *line)
{
	t_light_ambient	*light_ambient;

	(void)line;//todo: #3
	light_ambient = (t_light_ambient *)malloc(sizeof(t_light_ambient));
	if (light_ambient == NULL)
		return (NULL);
	light_ambient->bright = 0.1;
	light_ambient->color = (t_rgb){122, 255, 122};
	return (light_ambient);
}

t_light	*init_light(char *line)
{
	t_light	*light;

	(void)line;//todo: #3
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		return (NULL);
	light->pos = (t_vector){-5, 5, -5};
	light->bright = 0.5;
	return (light);
}
