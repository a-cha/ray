/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:08:56 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/31 21:33:27 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	cover(t_cy cy, t_ray ray, t_clst *cl_data, t_solve s)
{
	t_pl	plan;
	t_clst	cover;

	cover = (t_clst){INFINITY, (t_vect){0, 0, 0}, (t_vect){0, 0, 0}, CY};
	plan.or_d = cy.or_d;
	plan.d = s.v1;
	if ((encount_pl(plan, ray, &cover)))
		if (vect_len(vect_by_coods(cover.coord, s.v1)) > cy.width / 2)
			cover.dist = INFINITY;
	plan.d = s.v2;
	if ((encount_pl(plan, ray, &cover)))
		if (vect_len(vect_by_coods(cover.coord, s.v2)) > cy.width / 2)
			cover.dist = INFINITY;
	if (cover.dist < cl_data->dist)
	{
		cl_data->dist = cover.dist;
		cl_data->coord = cover.coord;
		cl_data->vect = cover.vect;
		cl_data->f = CY;
		return (1);
	}
	return (0);
}

static int	fill_data(t_cy cy, t_ray ray, t_clst *cl_data, t_solve s)
{
	s.v1 = vect_scale(vect_normalize(vect_by_coods(cy.d, cy.or_d)), \
															cy.height / 2);
	s.v2 = vect_scale(vect_normalize(vect_by_coods(cy.d, \
						vect_scale(cy.or_d, -1))), cy.height / 2);
	if (s.discrim >= 0 && s.t1 < cl_data->dist && s.t1 >= 0)
	{
		s.cross = vect_sum(ray.coord, vect_scale(ray.vect, s.t1));
		s.a = sqrt(pow(cy.width / 2, 2) + pow(cy.height / 2, 2));
		if (s.a >= vect_len(vect_by_coods(cy.d, s.cross)))
		{
			cl_data->dist = s.t1;
			cl_data->f = CY;
			cl_data->coord = s.cross;
			cl_data->vect = vect_normalize(vect_cross(vect_cross(\
					vect_by_coods(cy.d, cl_data->coord), cy.or_d), cy.or_d));
			s.x = 1;
		}
	}
	return ((cover(cy, ray, cl_data, s)) || s.x == 1 ? 1 : 0);
}

static int	encount_cy(t_cy cy, t_ray ray, t_clst *cl_data)
{
	t_solve	s;

	s.cross = vect_cross(ray.vect, cy.or_d);
	s.v1 = vect_by_coods(ray.coord, cy.d);
	s.v2 = vect_cross(s.v1, cy.or_d);
	s.a = vect_scalar(s.cross, s.cross);
	s.b = vect_scalar(s.cross, s.v2) * 2;
	s.c = vect_scalar(s.v2, s.v2) - (pow(cy.width / 2, 2) \
						* vect_scalar(cy.or_d, cy.or_d));
	s.discrim = pow(s.b, 2) - (4 * s.a * s.c);
	s.t1 = (s.b * -1 + sqrt(s.discrim)) / (2 * s.a);
	s.t2 = (s.b * -1 - sqrt(s.discrim)) / (2 * s.a);
	s.t1 = s.t1 > s.t2 ? s.t2 : s.t1;
	return (fill_data(cy, ray, cl_data, s));
}

void		draw_cylinder(t_list *cy, t_ray ray, void **obj, t_clst *cl_data)
{
	t_cy	*curr_cy;

	while (cy)
	{
		curr_cy = cy->content;
		if ((encount_cy(*curr_cy, ray, cl_data)))
			*obj = curr_cy;
		cy = cy->next;
	}
}
