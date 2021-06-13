/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:47:04 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 12:49:54 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect		*new_vect(double r, double g, double b)
{
	t_vect	*vec;

	if ((vec = malloc(sizeof(t_vect))))
	{
		vec->x = r;
		vec->y = g;
		vec->z = b;
	}
	return (vec);
}

t_vect		vect_normalize(t_vect d)
{
	t_vect	vect;
	double	len;

	len = vect_len(d);
	vect.x = d.x / len;
	vect.y = d.y / len;
	vect.z = d.z / len;
	return (vect);
}

double		vect_len(t_vect vect)
{
	double	len;

	len = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
	return (len);
}

t_vect		vect_by_coods(t_vect start, t_vect finish)
{
	t_vect	vect;

	vect.x = start.x - finish.x;
	vect.y = start.y - finish.y;
	vect.z = start.z - finish.z;
	return (vect);
}

double		vect_scalar(t_vect a, t_vect b)
{
	double	scal;

	scal = a.x * b.x + a.y * b.y + a.z * b.z;
	return (scal);
}
