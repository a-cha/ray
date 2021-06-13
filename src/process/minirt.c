/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:02:01 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/31 21:13:34 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			fill_img(t_scene *scene, t_list *cams)
{
	t_solve		s;
	double		scale;
	t_cam		*cam;
	int			col;

	cam = cams->data;
	scene->img = image_init(scene, scene->x, scene->y);
	scale = (((double)scene->x / 2) / tan((double)cam->fov / 2 * M_PI / 180));
	s.v1.z = 1;
	s.y = 0;
	while (s.y < scene->y)
	{
		s.x = 0;
		while (s.x < scene->x)
		{
			s.v1.x = (s.x - (double)scene->x / 2) / scale;
			s.v1.y = ((s.y - (double)scene->y / 2) * -1) / scale;
			col = trace_ray(scene, cam, s.v1);
			my_mlx_pixel_put(scene->img, s.x, s.y, col);
			s.x++;
		}
		s.y++;
	}
}

static void		scene_to_bmp(char const **av, t_scene *scene)
{
	if (ft_strncmp(av[2], "--save", 7))
		error_exit("Wrong second argument", ARGS_ERR, scene);
	else
	{
		fill_img(scene, scene->cam);
		create_bmp(scene);
		ft_putstr_fd("Screenshot created\n", 1);
		free_exit(scene);
		return ;
	}
}

void			push_img_to_win(t_scene *scene, t_list *cam)
{
	if (scene->img)
	{
		if (scene->img->img)
			mlx_destroy_image(scene->mlx_ptr, scene->img->img);
		free(scene->img);
		scene->img = NULL;
	}
	fill_img(scene, cam);
	mlx_put_image_to_window(scene->mlx_ptr, scene->window, \
											scene->img->img, 0, 0);
}

int				main(int ac, char const **av)
{
	t_scene		*scene;

	if (ac == 1 || ac > 3)
		error_exit("Error number of arguments", ARGS_ERR, NULL);
	scene = scene_struct();
	if (!(scene->mlx_ptr = mlx_init()))
		error_exit("Mlx connection error", MLX_ERR, scene);
	scene = parse(av[1], scene);
	if (av[2])
		scene_to_bmp(av, scene);
	else
	{
		if (!(scene->window = mlx_new_window(scene->mlx_ptr, \
										scene->x, scene->y, "Beautifully?")))
			error_exit("Error while window creating", MLX_ERR, scene);
		mlx_hook(scene->window, 17, 1L << 17, free_exit, scene);
		mlx_key_hook(scene->window, key_hook, scene);
		push_img_to_win(scene, scene->cam);
		mlx_loop(scene->mlx_ptr);
	}
	return (0);
}
