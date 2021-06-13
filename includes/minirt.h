/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:24:26 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/31 21:35:08 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "libasm.h"

/*
** ----- Error codes -----
*/
# define ARGS_ERR (1)
# define PARSE_ERR (2)
# define MLX_ERR (3)
# define MALLOC_ERR (4)
# define FILE_ERR (5)

/*
** ----- Defines for parsing -----
*/
# define PL (1)
# define SP (2)
# define SQ (3)
# define CY (4)
# define TR (5)

/*
** ----- Defines for processing -----
*/
# define EPSILON 1e-4
# define BMP_HEAD_S 14
# define BMP_INF_S 40

/*
** ----- Key's defines -----
*/
# define KEY_ESC 53
# define KEY_RIGHT 124
# define KEY_LEFT 123

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef struct		s_matr
{
	t_vect			vx;
	t_vect			vy;
	t_vect			vz;
}					t_matr;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef	struct		s_cam
{
	t_vect			c;
	t_vect			or_c;
	int				fov;
}					t_cam;

typedef	struct		s_light
{
	t_vect			l;
	double			bright;
	t_rgb			colour;
}					t_light;

typedef	struct		s_pl
{
	t_vect			d;
	t_vect			or_d;
	t_rgb			colour;
}					t_pl;

typedef	struct		s_sp
{
	t_vect			d;
	double			rad;
	t_rgb			colour;
}					t_sp;

typedef	struct		s_sq
{
	t_vect			d;
	t_vect			or_d;
	double			width;
	t_rgb			colour;
}					t_sq;

typedef	struct		s_cy
{
	t_vect			d;
	t_vect			or_d;
	double			width;
	double			height;
	t_rgb			colour;
}					t_cy;

typedef	struct		s_tr
{
	t_vect			d1;
	t_vect			d2;
	t_vect			d3;
	t_rgb			colour;
}					t_tr;

typedef struct		s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_image;

typedef	struct		s_scene
{
	int				x;
	int				y;
	double			amb;
	t_rgb			amb_col;
	t_list			*cam;
	t_list			*light;
	t_list			*pl;
	t_list			*sp;
	t_list			*sq;
	t_list			*cy;
	t_list			*tr;
	t_image			*img;
	void			*mlx_ptr;
	void			*window;
}					t_scene;

/*
** ----- Defines for processing -----
*/

typedef struct		s_ray
{
	t_vect			coord;
	t_vect			vect;
}					t_ray;

typedef struct		s_closest
{
	double			dist;
	t_vect			coord;
	t_vect			vect;
	char			f;
}					t_clst;

typedef struct		s_solve
{
	double			a;
	double			b;
	double			c;
	double			discrim;
	double			t1;
	double			t2;
	t_vect			cross;
	t_vect			v1;
	t_vect			v2;
	t_vect			v3;
	int				x;
	int				y;
}					t_solve;

/*
** ----- Parsing functions -----
*/
t_scene				*scene_struct(void);
t_scene				*parse(const char *path, t_scene *scene);
t_rgb				parse_colour(char *line);
void				parse_coord(char *line, double *x, double *y, double *z);
int					parse_ambient(char *line, t_scene **scene);
char				parse_light(char *line, t_scene **scene);
int					parse_cam(char *line, t_scene **scene);
char				parse_pl(char *line, t_scene **scene);
char				parse_sp(char *line, t_scene **scene);
char				parse_sq(char *line, t_scene **scene);
char				parse_tr(char *line, t_scene **scene);
char				parse_cy(char *line, t_scene **scene);
void				to_the_next_param(char **line);

/*
** ----- Processing functions -----
*/
void				my_mlx_pixel_put(t_image *data, int x, int y, int color);
void				create_bmp(t_scene *scene);
void				push_img_to_win(t_scene *scene, t_list *cam);
int					key_hook(int key, t_scene *scene);
int					trace_ray(t_scene *scene, t_cam *cam, t_vect d);
t_image				*image_init(t_scene *scene, int x, int y);

double				vect_len(t_vect vect);
t_vect				vect_normalize(t_vect d);
t_vect				vect_by_coods(t_vect start, t_vect finish);
double				vect_scalar(t_vect a, t_vect b);
t_ray				*new_ray(t_vect coord, t_vect vect);
t_vect				vect_scale(t_vect vect, double scale);
t_vect				vect_sum(t_vect a, t_vect b);
t_vect				*new_vect(double r, double g, double b);
void				vect_scale1(t_vect *vect, double scale);
void				vect_sum1(t_vect *a, t_vect b);
t_vect				vect_cross(t_vect a, t_vect b);
t_rgb				*vect_to_rgb(t_vect vect);
t_vect				matrix_vx(t_vect camera);
t_vect				matrix_scalar(t_matr m, t_vect v);

int					rgb_to_int(t_rgb col);
t_rgb				*rgb_new(t_rgb rgb);
t_rgb				rgb_scale(t_rgb rgb, double scale);
t_rgb				*rgb_sum(t_rgb *rgb, t_rgb plus);
void				rgb_stable(t_rgb *col);
void				rgb_multiple(t_rgb *mult, t_rgb col);
t_rgb				obj_col(void *obj, char f);

void				*closest_object(t_scene *scene, t_ray ray, t_clst *cl_data);
void				draw_sphere(t_list *sp, t_ray ray, void **obj, \
															t_clst *cl_data);
void				draw_plane(t_list *pl, t_ray ray, void **obj, \
															t_clst *cl_data);
void				draw_square(t_list *sq, t_ray ray, void **obj, \
															t_clst *cl_data);
void				draw_triangle(t_list *tr, t_ray ray, void **obj, \
															t_clst *cl_data);
void				draw_cylinder(t_list *cy, t_ray ray, void **obj, \
															t_clst *cl_data);
int					encount_pl(t_pl pl, t_ray ray, t_clst *cl_data);

void				error_exit(char *str, int err, t_scene *scene);
int					free_exit(t_scene *scene);

#endif
