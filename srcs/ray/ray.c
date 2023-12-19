#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "object.h"
#include "helpers.h"
#include "ray.h"
#include <stdio.h>
bool	is_shadow_intersection(\
	t_scene *scene, t_intersection intersection, bool is_camera_inside)
{
	const t_vector	ray_shadow = \
		vec_subtract(intersection.position, scene->light->pos);
	t_deque_node	*current_node;
	double			new_distance;
	double			light_distance;

	printf("is_shadow_intersection 影になるかチェック\n");
	//lightとカメラが球内外に別れている => 影 true
	if (is_camera_inside != \
		is_inside_sphere(scene->light->pos, intersection.object, ray_shadow))
	{
		printf("is_shadow 2a /*/is_in_sphere/*/\n");
		return (true);
	}
	current_node = scene->list_object->node;
	t_sphere *sphere = intersection.object;
//	light_distance = vec_norm(\
//		vec_subtract(scene->light->pos, intersection.position));//todo: あやしい
	light_distance = get_distance_to_sphere(\
				ray_shadow, scene->light->pos, intersection.object);
	printf("is_shadow 2 intersection.position:%f %f %f\n", intersection.position.x, intersection.position.y, intersection.position.z);
	printf("is_shadow 2 light_distance:%f\n", light_distance);
	while (current_node)
	{
		printf("is_shadow loopして確認中。 %hhu\n", sphere->color.g);
		if (current_node->content == intersection.object)
		{
			current_node = current_node->next;
			printf("is_shadow 相手が自分だった。 continue %hhu\n", sphere->color.g);
			continue ;
		}
		new_distance = get_distance_to_sphere(\
			ray_shadow, scene->light->pos, current_node->content);
		printf("is_shadow rayと他物体の距離 new_distance:%f\n", new_distance);
		if (!isnan(new_distance) && new_distance < light_distance)
		{
			printf("is_shadow こいつ自分とライトの間にいる！ %hhu\n", sphere->color.g);
			double self_distance = get_distance_to_sphere(\
				ray_shadow, scene->light->pos, intersection.object);
			printf("is_shadow rayと自分の距離 self_distance:%f\n", self_distance);
			return (true);
		}
		current_node = current_node->next;
	}
	printf("is_shadow 自分が一番ライトに近い。\n");
	return (false);
}
#include <stdio.h>
double	get_l_dot(\
	t_scene *scene, t_intersection intersection, bool is_camera_inside)
{
	double		l_dot;
	t_vector	incident;

	printf("/*/*/*/ get_l_dot 1\n");
	//この画素が影になるならNO_INCIDENT
	if (is_shadow_intersection(scene, intersection, is_camera_inside))
	{
		printf("get_l_dot 自分とライトの間に何かいて影になります\n");
		return (NO_INCIDENT);
	}
	//この画素が影にならないならincident（光の入射をとってきてl_dot計算）
	printf("get_l_dot 自分が一番ライトに近いので入射取りに行く\n");
	incident = vec_normalize(\
		vec_subtract(scene->light->pos, intersection.position));
	l_dot = vec_dot(incident, intersection.normal);
	printf("get_l_dot とってきたので。 l_dot: %f / incident: %f %f %f / intersection.normal: %f %f %f\n", l_dot, incident.x, incident.y, incident.z, intersection.normal.x, intersection.normal.y, intersection.normal.z);
	if (l_dot < 0)
		return (NO_INCIDENT);
	l_dot = clipping(l_dot, 0, 1);
	printf("get_l_dot 4 l_dot: %f // 明るい!!\n", l_dot);
	return (l_dot);
}

t_rgb_f	get_lux_ambient(const t_light_ambient *ambient)
{
	t_rgb_f	lux_ambient;

	lux_ambient.r = ambient->color.r / 255.0 * ambient->bright;
	lux_ambient.g = ambient->color.g / 255.0 * ambient->bright;
	lux_ambient.b = ambient->color.b / 255.0 * ambient->bright;
	return (lux_ambient);
}

t_rgb_f	get_lux_light(const t_light *light, t_rgb color, double l_dot)
{
	t_rgb_f	lux_light;

	lux_light.r = color.r / 255.0 * light->bright * l_dot;
	lux_light.g = color.g / 255.0 * light->bright * l_dot;
	lux_light.b = color.b / 255.0 * light->bright * l_dot;
	return (lux_light);
}

t_rgb_f	get_lux_total(t_rgb_f lux_ambient, t_rgb_f lux_light)
{
	t_rgb_f	lux_total;

	lux_total.r = clipping(lux_ambient.r + lux_light.r, 0, 1);
	lux_total.g = clipping(lux_ambient.g + lux_light.g, 0, 1);
	lux_total.b = clipping(lux_ambient.b + lux_light.b, 0, 1);
	return (lux_total);
}
