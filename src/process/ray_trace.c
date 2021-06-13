/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:18:08 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:32:55 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vect	*calculate_light(t_scene *scene, t_light *curr_l, t_clst data)
{
	double		scalar;
	void		*obstacle;
	t_clst		*data_obstacle;
	t_ray		to_light;
	t_vect		*l_col;

	if (!(l_col = new_vect((double)curr_l->colour.r / 255, \
			(double)curr_l->colour.g / 255, (double)curr_l->colour.b / 255)))
		error_exit("Malloc error", MALLOC_ERR, scene);
	if (!(data_obstacle = malloc(sizeof(t_clst))))
	{
		free(l_col);
		error_exit("Malloc error", MALLOC_ERR, scene);
	}
	data_obstacle->dist = INFINITY;
	vect_scale1(l_col, curr_l->bright);
	to_light.coord = data.coord;
	to_light.vect = vect_normalize(vect_by_coods(curr_l->l, to_light.coord));
	obstacle = closest_object(scene, to_light, data_obstacle);
	((data_obstacle->dist > (vect_len(vect_by_coods(\
			curr_l->l, data.coord))) || !obstacle) && \
		(scalar = vect_scalar(data.vect, to_light.vect)) >= 0) \
		? vect_scale1(l_col, scalar) : vect_scale1(l_col, 0);
	free(data_obstacle);
	return (l_col);
}

static t_rgb	*get_light(t_scene *scene, t_list *lights, t_clst data)
{
	t_light		*curr_l;
	t_rgb		*res;
	t_vect		*light;
	t_vect		*l_col;

	if (!(light = new_vect(0, 0, 0)))
		error_exit("Malloc error", MALLOC_ERR, scene);
	while (lights)
	{
		curr_l = lights->content;
		l_col = calculate_light(scene, curr_l, data);
		vect_sum1(light, *l_col);
		free(l_col);
		lights = lights->next;
	}
	if (!(res = vect_to_rgb(*light)))
	{
		free(light);
		error_exit("Malloc error", MALLOC_ERR, scene);
	}
	free(light);
	return (res);
}

static int		get_colour(t_scene *scene, t_ray ray)
{
	t_rgb		col;
	t_rgb		*col1;
	int			colour;
	void		*obj;
	t_clst		*cl_data;

	if (!(cl_data = malloc(sizeof(t_clst))))
		error_exit("Malloc error", MALLOC_ERR, scene);
	cl_data->dist = INFINITY;
	obj = closest_object(scene, ray, cl_data);
	col = (t_rgb){0, 0, 0};
	if (obj)
	{
		col = obj_col(obj, cl_data->f);
		rgb_multiple(&col, rgb_scale(scene->amb_col, scene->amb));
		col1 = get_light(scene, scene->light, *cl_data);
		rgb_sum(col1, col);
		rgb_stable(col1);
		colour = rgb_to_int(*col1);
		free(col1);
	}
	else
		colour = rgb_to_int(col);
	free(cl_data);
	return (colour);
}

int				trace_ray(t_scene *scene, t_cam *cam, t_vect d)
{
	t_ray		*ray;
	int			col;
	t_matr		matrix;

	matrix.vx = matrix_vx(cam->or_c);
	matrix.vy = vect_cross(cam->or_c, matrix.vx);
	matrix.vz = vect_scale(cam->or_c, -1);
	matrix.vx = vect_normalize(matrix.vx);
	matrix.vy = vect_normalize(matrix.vy);
	matrix.vz = vect_normalize(matrix.vz);
	ray = new_ray(cam->c, vect_scale(vect_normalize(\
										matrix_scalar(matrix, d)), -1));
	col = get_colour(scene, *ray);
	free(ray);
	return (col);
}
