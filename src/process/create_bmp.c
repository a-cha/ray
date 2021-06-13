/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:28:34 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/30 13:28:34 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			bitmap_f_hed(t_scene *scene, int p_size, int fd)
{
	unsigned char	*file_header;
	int				file_size;

	if (!(file_header = ft_calloc(BMP_HEAD_S, sizeof(unsigned char))))
		error_exit("Malloc", MALLOC_ERR, scene);
	file_size = BMP_HEAD_S + BMP_INF_S + \
						(scene->img->bpp / 8 * scene->x + p_size) * scene->y;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(BMP_HEAD_S + BMP_INF_S);
	write(fd, file_header, BMP_HEAD_S);
	free(file_header);
	file_header = NULL;
}

static void			bitmap_i_hed(t_scene *scene, int fd)
{
	unsigned char	*info_header;

	if (!(info_header = ft_calloc(BMP_INF_S, sizeof(unsigned char))))
		error_exit("Malloc", MALLOC_ERR, scene);
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(scene->x);
	info_header[5] = (unsigned char)(scene->x >> 8);
	info_header[6] = (unsigned char)(scene->x >> 16);
	info_header[7] = (unsigned char)(scene->x >> 24);
	info_header[8] = (unsigned char)(scene->y);
	info_header[9] = (unsigned char)(scene->y >> 8);
	info_header[10] = (unsigned char)(scene->y >> 16);
	info_header[11] = (unsigned char)(scene->y >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(scene->img->bpp);
	write(fd, info_header, BMP_INF_S);
	free(info_header);
	info_header = NULL;
}

void				create_bmp(t_scene *scene)
{
	int				i;
	int				fd;
	int				p_size;
	unsigned char	padding[3];

	i = scene->y;
	ft_bzero(padding, 3);
	if (!(fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		error_exit("Fail to export bmp file", FILE_ERR, scene);
	p_size = (4 - (scene->x * scene->img->bpp / 8) % 4) % 4;
	bitmap_f_hed(scene, p_size, fd);
	bitmap_i_hed(scene, fd);
	while (i >= 0)
	{
		write(fd, scene->img->addr + \
					(i * scene->x * scene->img->bpp / 8), scene->img->line_len);
		write(fd, padding, p_size);
		i--;
	}
	close(fd);
}
