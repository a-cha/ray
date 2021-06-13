/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:08:39 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:08:39 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			rgb_to_int(t_rgb col)
{
	int		colour;

	colour = 0;
	col.r = col.r << 16;
	col.g = col.g << 8;
	colour = colour | col.r;
	colour = colour | col.g;
	colour = colour | col.b;
	return (colour);
}

t_rgb		*vect_to_rgb(t_vect vect)
{
	t_rgb	col;

	col.r = vect.x * 255;
	col.g = vect.y * 255;
	col.b = vect.z * 255;
	return (rgb_new(col));
}
