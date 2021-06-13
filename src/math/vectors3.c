/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:59:45 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:00:01 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		vect_sum1(t_vect *a, t_vect b)
{
	a->x = a->x + b.x;
	a->y = a->y + b.y;
	a->z = a->z + b.z;
}

t_vect		vect_sum(t_vect a, t_vect b)
{
	t_vect	vect;

	vect.x = a.x + b.x;
	vect.y = a.y + b.y;
	vect.z = a.z + b.z;
	return (vect);
}
