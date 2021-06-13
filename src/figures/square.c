/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:15:11 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:15:22 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	encount_sq(t_sq sq, t_ray ray, t_clst *cl_data)
{
	t_solve	s;

	s.a = vect_scalar(vect_by_coods(ray.coord, sq.d), sq.or_d);
	s.b = vect_scalar(ray.vect, sq.or_d);
	if (fabs(s.b) < EPSILON || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return (0);
	s.t1 = -s.a / s.b;
	s.cross = vect_by_coods(\
			vect_sum(vect_scale(ray.vect, s.t1), ray.coord), sq.d);
	s.t2 = sq.width / 2;
	if (fabs(s.cross.x) > s.t2 || fabs(s.cross.y) > s.t2 || \
												fabs(s.cross.z) > s.t2)
		return (0);
	if (s.t1 > EPSILON && s.t1 < cl_data->dist)
	{
		cl_data->dist = s.t1;
		cl_data->f = SQ;
		cl_data->coord = vect_sum(ray.coord, vect_scale(ray.vect, s.t1));
		cl_data->vect = sq.or_d;
		return (1);
	}
	return (0);
}

void		draw_square(t_list *sq, t_ray ray, void **obj, t_clst *cl_data)
{
	t_sq	*curr_sq;

	while (sq)
	{
		curr_sq = sq->content;
		if ((encount_sq(*curr_sq, ray, cl_data)))
			*obj = curr_sq;
		sq = sq->next;
	}
}
