/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 22:32:53 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 12:42:57 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	parse_resolution(char *line, t_scene **scene)
{
	int		screenx;
	int		screeny;
	int		lol;
	double	kek;

	mlx_get_screen_size((*scene)->mlx_ptr, &screenx, &screeny);
	to_the_next_param(&line);
	if (((*scene)->x = ft_atoi(line)) > screenx)
		(*scene)->x = screenx;
	lol = (*scene)->x / 64;
	kek = (*scene)->x % 64;
	if (kek != 0)
	{
		if (kek >= 0.5)
			(*scene)->x = 64 * (lol + 1);
		else
			(*scene)->x = 64 * lol;
	}
	to_the_next_param(&line);
	if (((*scene)->y = ft_atoi(line)) > screeny)
		(*scene)->y = screeny;
	return (100);
}

static int	switch_to(char *line, t_scene **scene)
{
	int		res;

	res = -1;
	if (!ft_strncmp(line, "# ", 2))
		res = 0;
	else if (!ft_strncmp(line, "R ", 2))
		res = (int)parse_resolution(line, scene);
	else if (!ft_strncmp(line, "A ", 2))
		res = parse_ambient(line, scene);
	else if (!ft_strncmp(line, "c ", 2))
		res = parse_cam(line, scene);
	else if (!ft_strncmp(line, "l ", 2))
		res = (int)parse_light(line, scene);
	else if (!ft_strncmp(line, "pl ", 3))
		res = (int)parse_pl(line, scene);
	else if (!ft_strncmp(line, "sp ", 3))
		res = (int)parse_sp(line, scene);
	else if (!ft_strncmp(line, "sq ", 3))
		res = (int)parse_sq(line, scene);
	else if (!ft_strncmp(line, "cy ", 3))
		res = (int)parse_cy(line, scene);
	else if (!ft_strncmp(line, "tr ", 3))
		res = (int)parse_tr(line, scene);
	return (res);
}

static void	handle_errors(int res_parse, t_scene *scene)
{
	if (res_parse < 10000)
		error_exit("Where is camera?", PARSE_ERR, scene);
	if (res_parse > 10000)
	{
		if ((res_parse % 10000) < 300)
		{
			if ((res_parse % 10000) % 300 < 100)
				error_exit("Resolution and ambient are required", \
															PARSE_ERR, scene);
			if ((res_parse % 10000) % 300 > 100 && \
											(res_parse % 10000) % 300 < 200)
				error_exit("Need ambient", PARSE_ERR, scene);
			if ((res_parse % 10000) % 300 > 200)
				error_exit("Need resolution", PARSE_ERR, scene);
		}
	}
	if (!((res_parse - 300) % 10000))
		error_exit("Nothing to draw", PARSE_ERR, scene);
}

t_scene		*parse(const char *path, t_scene *scene)
{
	short	fd;
	char	res_gnl;
	int		res_parse;
	char	*line;

	if (ft_strncmp(path + ft_strlen(path) - 3, ".rt", 4))
		error_exit("Error file type", PARSE_ERR, NULL);
	if ((fd = (short)open(path, O_RDONLY)) == -1)
		error_exit("Error opening file", PARSE_ERR, NULL);
	res_parse = 0;
	while ((res_gnl = (char)get_next_line(fd, &line)) >= -1)
	{
		if (res_gnl == -1)
			error_exit("GNL error", PARSE_ERR, scene);
		if (*line)
			if ((res_parse += switch_to(line, &scene)) == -1)
				error_exit("Unexpected symbols", PARSE_ERR, scene);
		free(line);
		if (res_gnl == 0)
			break ;
	}
	handle_errors(res_parse, scene);
	return (scene);
}
