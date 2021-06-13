/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:31:43 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/29 14:31:43 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		parse_cy(char *line, t_scene **scene)
{
	t_cy	*cy;
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		error_exit("Malloc error", MALLOC_ERR, *scene);
	if ((cy = (t_cy *)malloc(sizeof(t_cy))))
	{
		to_the_next_param(&line);
		parse_coord(line, &(cy->d.x), &(cy->d.y), &(cy->d.z));
		to_the_next_param(&line);
		parse_coord(line, &(cy->or_d.x), &(cy->or_d.y), &(cy->or_d.z));
		to_the_next_param(&line);
		cy->width = ft_atof(line);
		to_the_next_param(&line);
		cy->height = ft_atof(line);
		to_the_next_param(&line);
		cy->colour = parse_colour(line);
		list->content = cy;
		ft_lstadd_front(&((*scene)->cy), list);
	}
	else
		error_exit("Malloc error", MALLOC_ERR, *scene);
	return (1);
}
