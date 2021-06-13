/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:31:51 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 12:45:04 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		parse_light(char *line, t_scene **scene)
{
	t_light	*light;
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		error_exit("Malloc error", MALLOC_ERR, *scene);
	if ((light = (t_light *)malloc(sizeof(t_light))))
	{
		to_the_next_param(&line);
		parse_coord(line, &(light->l.x), &(light->l.y), &(light->l.z));
		to_the_next_param(&line);
		light->bright = ft_atof(line);
		to_the_next_param(&line);
		light->colour = parse_colour(line);
		list->content = light;
		ft_lstadd_front(&((*scene)->light), list);
	}
	else
		error_exit("Malloc error", MALLOC_ERR, *scene);
	return (0);
}

int			parse_ambient(char *line, t_scene **scene)
{
	while (!ft_isdigit(*line))
		line++;
	(*scene)->amb = ft_atof(line);
	to_the_next_param(&line);
	(*scene)->amb_col = parse_colour(line);
	return (200);
}
