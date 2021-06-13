/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:23:51 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 16:19:07 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_delete(void *content)
{
	free(content);
	content = NULL;
}

static void	free_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->img)
		{
			free(scene->img);
			if (scene->img->img)
				mlx_destroy_image(scene->mlx_ptr, scene->img->img);
		}
		if (scene->window)
			mlx_destroy_window(scene->mlx_ptr, scene->window);
		ft_lstclear(&(scene->light), ft_delete);
		if (scene->cam)
			ft_lstclear(&(scene->cam), ft_delete);
		ft_lstclear(&(scene->pl), ft_delete);
		ft_lstclear(&(scene->sp), ft_delete);
		ft_lstclear(&(scene->sq), ft_delete);
		ft_lstclear(&(scene->cy), ft_delete);
		ft_lstclear(&(scene->tr), ft_delete);
		free(scene);
		scene = NULL;
	}
}

void		error_exit(char *str, int err, t_scene *scene)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" (exit code: ", 2);
	ft_putnbr_fd(err, 2);
	ft_putstr_fd(")\n", 2);
	free_scene(scene);
	exit(err);
}

int			free_exit(t_scene *scene)
{
	free_scene(scene);
	ft_putstr_fd("Grade me as 100/100!\n", 1);
	exit(0);
}
