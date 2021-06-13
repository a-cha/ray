/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:32:21 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/29 14:32:21 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		parse_sq(char *line, t_scene **scene)
{
	t_sq	*sq;
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		error_exit("Malloc error", MALLOC_ERR, *scene);
	if ((sq = (t_sq *)malloc(sizeof(t_sq))))
	{
		to_the_next_param(&line);
		parse_coord(line, &(sq->d.x), &(sq->d.y), &(sq->d.z));
		to_the_next_param(&line);
		parse_coord(line, &(sq->or_d.x), &(sq->or_d.y), &(sq->or_d.z));
		to_the_next_param(&line);
		sq->width = ft_atof(line);
		to_the_next_param(&line);
		sq->colour = parse_colour(line);
		list->content = sq;
		ft_lstadd_front(&((*scene)->sq), list);
	}
	else
		error_exit("Malloc error", MALLOC_ERR, *scene);
	return (1);
}
