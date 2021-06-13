/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:32:27 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 12:46:25 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb		parse_colour(char *line)
{
	t_rgb	col;

	col.r = ft_atoi(line);
	while (*line != ',')
		line++;
	col.g = ft_atoi(++line);
	while (*line != ',')
		line++;
	col.b = ft_atoi(++line);
	return (col);
}

void		parse_coord(char *line, double *x, double *y, double *z)
{
	*x = ft_atof(line);
	while (*line != ',')
		line++;
	*y = ft_atof(++line);
	while (*line != ',')
		line++;
	*z = ft_atof(++line);
}

void		to_the_next_param(char **line)
{
	while (**line != ' ')
		(*line)++;
	while (**line == ' ')
		(*line)++;
}

t_scene		*scene_struct(void)
{
	t_scene	*scene;

	if (!(scene = malloc(sizeof(t_scene))))
		error_exit("Malloc error", MALLOC_ERR, scene);
	scene->x = 0;
	scene->y = 0;
	scene->amb = 0;
	scene->amb_col = (t_rgb){0, 0, 0};
	scene->cam = 0;
	scene->light = 0;
	scene->pl = 0;
	scene->sp = 0;
	scene->sq = 0;
	scene->cy = 0;
	scene->tr = 0;
	scene->mlx_ptr = 0;
	scene->window = 0;
	scene->img = 0;
	return (scene);
}
