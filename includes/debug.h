#ifndef DEBUG_H
# define DEBUG_H

# include "object.h"
# include "scene.h"

void	debug_print_scene_value(const t_scene *scene);
void	print_2d_array(char **strs);
void	debug_print_vector(const char *name, const t_vector vec);
void	debug_print_rgb(const char *name, const t_rgb rgb);
void	debug_print_sphere(t_sphere *sphere);
void	debug_print_plane(t_plane *plane);
void	debug_print_cylinder(t_cylinder *cylinder);

#endif
