/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:50:04 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 12:59:28 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect		vect_cross(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vect		matrix_vx(t_vect camera)
{
	t_vect	vx;

	if (camera.z)
	{
		vx.y = 0;
		vx.z = 0;
		vx.x = camera.z > 0 ? -1 : 1;
	}
	if (camera.x)
	{
		vx.y = 0;
		vx.x = 0;
		vx.z = camera.x > 0 ? 1 : -1;
	}
	if (camera.y)
	{
		vx.y = 0;
		vx.z = 0;
		vx.x = camera.y > 0 ? -1 : 1;
	}
	return (vx);
}

t_vect		matrix_scalar(t_matr m, t_vect v)
{
	t_vect	mv;

	mv.x = v.x * m.vx.x + v.y * m.vy.x + v.z * m.vz.x;
	mv.y = v.x * m.vx.y + v.y * m.vy.y + v.z * m.vz.y;
	mv.z = v.x * m.vx.z + v.y * m.vy.z + v.z * m.vz.z;
	return (mv);
}

void		vect_scale1(t_vect *vect, double scale)
{
	vect->x = vect->x * scale;
	vect->y = vect->y * scale;
	vect->z = vect->z * scale;
}

t_vect		vect_scale(t_vect vect, double scale)
{
	t_vect	v;

	v.x = vect.x * scale;
	v.y = vect.y * scale;
	v.z = vect.z * scale;
	return (v);
}
