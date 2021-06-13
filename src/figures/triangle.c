/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:14:14 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:14:23 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	fill_cl_data(t_ray ray, t_clst *cl_data, t_solve s)
{
	cl_data->dist = s.t1;
	cl_data->f = TR;
	cl_data->coord = vect_sum(ray.coord, vect_scale(ray.vect, cl_data->dist));
	cl_data->vect = vect_normalize(s.v1);
	return (1);
}

static int	encount_tr(t_tr tr, t_ray ray, t_clst *cl_data)
{
	t_solve	s;
	t_vect	v1;
	t_vect	v2;

	v1 = vect_by_coods(tr.d2, tr.d1);
	v2 = vect_by_coods(tr.d3, tr.d1);
	s.v1 = vect_cross(ray.vect, v2);
	s.discrim = vect_scalar(v1, s.v1);
	if (fabs(s.discrim) < EPSILON)
		return (0);
	s.c = 1 / s.discrim;
	s.v2 = vect_by_coods(ray.coord, tr.d1);
	s.a = vect_scalar(s.v2, s.v1) * s.c;
	if (s.a < EPSILON || s.a > 1)
		return (0);
	s.v2 = vect_cross(s.v2, v1);
	s.b = vect_scalar(ray.vect, s.v2) * s.c;
	if (s.b < EPSILON || s.a + s.b > 1)
		return (0);
	if ((s.t1 = vect_scalar(v2, s.v2) * s.c) < cl_data->dist)
		return (fill_cl_data(ray, cl_data, s));
	return (0);
}

void		draw_triangle(t_list *tr, t_ray ray, void **obj, t_clst *cl_data)
{
	t_tr	*curr_tr;

	while (tr)
	{
		curr_tr = tr->content;
		if ((encount_tr(*curr_tr, ray, cl_data)))
			*obj = curr_tr;
		tr = tr->next;
	}
}
