/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:32:05 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/29 14:32:05 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		parse_pl(char *line, t_scene **scene)
{
	t_pl	*pl;
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		error_exit("Malloc error", MALLOC_ERR, *scene);
	if ((pl = (t_pl *)malloc(sizeof(t_pl))))
	{
		to_the_next_param(&line);
		parse_coord(line, &(pl->d.x), &(pl->d.y), &(pl->d.z));
		to_the_next_param(&line);
		parse_coord(line, &(pl->or_d.x), &(pl->or_d.y), &(pl->or_d.z));
		to_the_next_param(&line);
		pl->colour = parse_colour(line);
		list->content = pl;
		ft_lstadd_front(&((*scene)->pl), list);
	}
	else
		error_exit("Malloc error", MALLOC_ERR, *scene);
	return (1);
}
