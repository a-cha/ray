/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:08:44 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 22:54:53 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->line_len + x * (data->bpp / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

t_image		*image_init(t_scene *scene, int x, int y)
{
	t_image	*img;

	if ((img = malloc(sizeof(t_image))))
	{
		if (!(img->img = mlx_new_image(scene->mlx_ptr, x, y)))
			error_exit("Minilibx error", MLX_ERR, scene);
		if (!(img->addr = mlx_get_data_addr(img->img, &img->bpp, \
												&img->line_len, &img->endian)))
			error_exit("Minilibx error", MLX_ERR, scene);
	}
	return (img);
}

t_ray		*new_ray(t_vect coord, t_vect vect)
{
	t_ray	*ray;

	if ((ray = malloc(sizeof(t_ray))))
	{
		ray->coord = coord;
		ray->vect = vect;
	}
	return (ray);
}

void		*closest_object(t_scene *scene, t_ray ray, t_clst *cl_data)
{
	void	*obj;

	obj = NULL;
	if (scene->pl)
		draw_plane(scene->pl, ray, &obj, cl_data);
	if (scene->sp)
		draw_sphere(scene->sp, ray, &obj, cl_data);
	if (scene->sq)
		draw_square(scene->sq, ray, &obj, cl_data);
	if (scene->tr)
		draw_triangle(scene->tr, ray, &obj, cl_data);
	if (scene->cy)
		draw_cylinder(scene->cy, ray, &obj, cl_data);
	return (obj);
}

t_rgb		obj_col(void *obj, char f)
{
	t_rgb	col;

	col = (t_rgb){0, 0, 0};
	if (f == PL)
		col = ((t_pl *)obj)->colour;
	else if (f == SP)
		col = ((t_sp *)obj)->colour;
	else if (f == SQ)
		col = ((t_sq *)obj)->colour;
	else if (f == CY)
		col = ((t_cy *)obj)->colour;
	else if (f == TR)
		col = ((t_tr *)obj)->colour;
	return (col);
}
