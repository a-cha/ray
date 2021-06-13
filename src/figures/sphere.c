/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:13:35 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:13:35 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		encount_sp(t_sp sp, t_ray ray, t_clst *cl_data)
{
	t_solve	solve;
	t_vect	cent;

	solve.a = vect_scalar(ray.vect, ray.vect);
	cent = vect_by_coods(ray.coord, sp.d);
	solve.b = 2 * vect_scalar(cent, ray.vect);
	solve.c = pow(vect_len(cent), 2) - pow(sp.rad, 2);
	solve.discrim = solve.b * solve.b - 4 * solve.a * solve.c;
	solve.t1 = (solve.b * -1 + sqrt(solve.discrim)) / 2 * solve.a;
	solve.t2 = (solve.b * -1 - sqrt(solve.discrim)) / 2 * solve.a;
	solve.t1 = solve.t1 > solve.t2 ? solve.t2 : solve.t1;
	if (solve.discrim >= 0 && solve.t1 < cl_data->dist && solve.t1 >= 0)
	{
		cl_data->dist = solve.t1;
		cl_data->f = SP;
		cl_data->coord = vect_sum(ray.coord, vect_scale(ray.vect, solve.t1));
		cl_data->vect = vect_normalize(vect_by_coods(cl_data->coord, sp.d));
		return (1);
	}
	return (0);
}

void	draw_sphere(t_list *sp, t_ray ray, void **obj, t_clst *cl_data)
{
	t_sp		*curr_sp;

	while (sp)
	{
		curr_sp = sp->content;
		if ((encount_sp(*curr_sp, ray, cl_data)))
			*obj = curr_sp;
		sp = sp->next;
	}
}
