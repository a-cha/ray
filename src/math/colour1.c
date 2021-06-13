/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:06:12 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:11:33 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb		*rgb_new(t_rgb rgb)
{
	t_rgb	*col;

	if ((col = malloc(sizeof(t_rgb))))
	{
		col->r = rgb.r;
		col->g = rgb.g;
		col->b = rgb.b;
	}
	return (col);
}

t_rgb		rgb_scale(t_rgb rgb, double scale)
{
	t_rgb	col;

	col = (t_rgb){0, 0, 0};
	col.r = rgb.r * scale;
	col.g = rgb.g * scale;
	col.b = rgb.b * scale;
	return (col);
}

t_rgb		*rgb_sum(t_rgb *rgb, t_rgb plus)
{
	rgb->r += plus.r;
	rgb->g += plus.g;
	rgb->b += plus.b;
	return (rgb);
}

void		rgb_stable(t_rgb *col)
{
	if (col->r > 255)
		col->r = 255;
	if (col->g > 255)
		col->g = 255;
	if (col->b > 255)
		col->b = 255;
}

void		rgb_multiple(t_rgb *mult, t_rgb col)
{
	t_rgb	c;

	c.r = mult->r * col.r;
	mult->r = c.r / 255;
	c.g = mult->g * col.g;
	mult->g = c.g / 255;
	c.b = mult->b * col.b;
	mult->b = c.b / 255;
}
