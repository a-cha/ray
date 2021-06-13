/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:31:30 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/29 14:31:30 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			parse_cam(char *line, t_scene **scene)
{
	t_cam	*cam;
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		error_exit("Malloc error", MALLOC_ERR, *scene);
	if ((cam = (t_cam *)malloc(sizeof(t_cam))))
	{
		to_the_next_param(&line);
		parse_coord(line, &(cam->c.x), &(cam->c.y), &(cam->c.z));
		to_the_next_param(&line);
		parse_coord(line, &(cam->or_c.x), &(cam->or_c.y), &(cam->or_c.z));
		to_the_next_param(&line);
		cam->fov = ft_atoi(line);
		list->content = cam;
		ft_lstadd_front(&((*scene)->cam), list);
	}
	else
		error_exit("Malloc error", MALLOC_ERR, *scene);
	return (10000);
}
