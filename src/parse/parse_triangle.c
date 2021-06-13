/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:32:56 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/29 14:32:56 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		parse_tr(char *line, t_scene **scene)
{
	t_tr	*tr;
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		error_exit("Malloc error", MALLOC_ERR, *scene);
	if ((tr = (t_tr *)malloc(sizeof(t_tr))))
	{
		to_the_next_param(&line);
		parse_coord(line, &(tr->d1.x), &(tr->d1.y), &(tr->d1.z));
		to_the_next_param(&line);
		parse_coord(line, &(tr->d2.x), &(tr->d2.y), &(tr->d2.z));
		to_the_next_param(&line);
		parse_coord(line, &(tr->d3.x), &(tr->d3.y), &(tr->d3.z));
		to_the_next_param(&line);
		tr->colour = parse_colour(line);
		list->data = tr;
		ft_lstadd_front(&((*scene)->tr), list);
	}
	else
		error_exit("Malloc error", MALLOC_ERR, *scene);
	return (1);
}
