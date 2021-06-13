/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:32:15 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/29 14:32:15 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		parse_sp(char *line, t_scene **scene)
{
	t_sp	*sp;
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		error_exit("Malloc error", MALLOC_ERR, *scene);
	if ((sp = (t_sp *)malloc(sizeof(t_sp))))
	{
		to_the_next_param(&line);
		parse_coord(line, &(sp->d.x), &(sp->d.y), &(sp->d.z));
		to_the_next_param(&line);
		sp->rad = ft_atof(line);
		to_the_next_param(&line);
		sp->colour = parse_colour(line);
		list->content = sp;
		ft_lstadd_front(&((*scene)->sp), list);
	}
	else
		error_exit("Malloc error", MALLOC_ERR, *scene);
	return (1);
}
