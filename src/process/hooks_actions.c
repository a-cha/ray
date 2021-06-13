/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:06:02 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 12:09:51 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*suka(t_list *cam)
{
	t_list		*suka;

	suka = cam;
	return (suka);
}

static void		turn_cam_right(t_scene *scene, int n)
{
	t_list		*current;
	int			s;

	if (scene->cam->next)
	{
		s = ft_lstsize(scene->cam);
		n %= s;
		n += s;
		current = suka(scene->cam);
		while (n--)
		{
			if (current->next)
				current = current->next;
			else
				current = suka(scene->cam);
		}
		push_img_to_win(scene, current);
	}
}

static void		turn_cam_left(t_scene *scene, int n)
{
	int			s;

	s = ft_lstsize(scene->cam);
	n %= s;
	n += s;
	turn_cam_right(scene, n);
}

int				key_hook(int key, t_scene *scene)
{
	static int	n;

	if (key == KEY_ESC)
		free_exit(scene);
	else if (key == KEY_RIGHT)
	{
		n++;
		turn_cam_right(scene, n);
	}
	else if (key == KEY_LEFT)
	{
		n--;
		turn_cam_left(scene, n);
	}
	return (0);
}
