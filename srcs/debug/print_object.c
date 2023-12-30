#include "debug.h"
#include <stdio.h>

void	debug_print_sphere(t_sphere *sphere)
{
	debug_print_vector("sphere->center", sphere->center);
	printf("sphere->diameter = %f\n", sphere->diameter);
	debug_print_rgb("sphere->color", sphere->color);
}

void	debug_print_plane(t_plane *plane)
{
	debug_print_vector("plane->point", plane->point);
	debug_print_vector("plane->dir_n", plane->normal);
	debug_print_rgb("plane->color", plane->color);
}

void	debug_print_cylinder(t_cylinder *cylinder)
{
	debug_print_vector("cylinder->center", cylinder->center);
	debug_print_vector("cylinder->normal", cylinder->normal);
	printf("cylinder->diameter = %f\n", cylinder->diameter);
	printf("cylinder->height = %f\n", cylinder->height);
	debug_print_rgb("cylinder->color", cylinder->color);
}
