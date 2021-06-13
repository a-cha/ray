/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:12:24 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:12:24 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			encount_pl(t_pl pl, t_ray ray, t_clst *cl_data)
{
	t_solve	s;

	s.a = vect_scalar(pl.or_d, ray.vect);
	if (s.a != 0)
	{
		s.b = vect_scalar(vect_by_coods(pl.d, ray.coord), pl.or_d) / s.a;
		if (s.b > EPSILON && s.b < cl_data->dist)
		{
			cl_data->dist = s.b;
			cl_data->f = PL;
			cl_data->vect = pl.or_d;
			cl_data->coord = vect_sum(ray.coord, vect_scale(ray.vect, s.b));
			cl_data->coord = vect_sum(cl_data->coord, \
											vect_scale(cl_data->vect, EPSILON));
			return (1);
		}
	}
	return (0);
}

void		draw_plane(t_list *pl, t_ray ray, void **obj, t_clst *cl_data)
{
	t_pl	*curr_pl;

	while (pl)
	{
		curr_pl = pl->content;
		if ((encount_pl(*curr_pl, ray, cl_data)))
			*obj = curr_pl;
		pl = pl->next;
	}
}
