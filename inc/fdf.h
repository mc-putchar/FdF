/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:15:55 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:32:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "keycodes.h"
# include "error_handler.h"

# define USAGE			"usage: ./fdf <filename>"
# define TITLE			"FdF"
# define HEX_BASE		"0123456789ABCDEF"
# define READ_BLOCK		4096
# define WIN_WIDTH		1920
# define WIN_HEIGHT		1200
# define MENU_WIDTH		300
# define MENU_HEIGHT	WIN_HEIGHT
# define IMG_WIDTH		(WIN_WIDTH - MENU_WIDTH)
# define IMG_HEIGHT		WIN_HEIGHT
# define IMG_X_OFFSET	(MENU_WIDTH)
# define IMG_Y_OFFSET	0
# define MENU_X_OFFSET	0
# define MENU_Y_OFFSET	0
# define MENU_BG_COLOR	0x00222222
# define TXT_COLOR		0x00FFFFFF
# define IMG_BG_COLOR	0x001E1E1E
# define ISOMETRIC		1
# define PARALLEL		2
# define ROT_STEP		0.05
# define ZOOM_STEP		1
# define OFFSET_STEP	10
# define Z_DIVISOR		100
# define ISO_ANGLE		0.523599
# define CHECK_ROWS		1
# define COLOR_DEFAULT	0
# define COLOR_HEIGHT	1

typedef struct s_map
{
	char			*path;
	int				width;
	int				height;
	int				**z;
	int				**c;
	int				**c_norm;
	int				init;
	int				z_min;
	int				z_max;
}	t_map;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}	t_point;

typedef struct s_img_data
{
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img_data;

typedef struct s_cam
{
	int		zoom;
	int		x_offset;
	int		y_offset;
	double	z_divisor;
	float	alpha;
	float	beta;
	float	gamma;
	int		projection;
}	t_cam;

typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	t_img_data		*img_data;
	void			*menu;
	t_img_data		*menu_data;
	t_map			*map;
	t_cam			*cam;
	double			iso_cos;
	double			iso_sin;
	int				color_mode;
}	t_fdf;

int		normalize_colors(t_map *map);
t_map	*parse_map(char *path);
int		free_map(t_map *map);
int		free_arr(char **array);
int		free_fdf(t_fdf *fdf);
void	free_matrix(int **matrix, int height);

t_fdf	*init_fdf(char *path);
void	init_hooks(t_fdf *fdf);
void	init_img(t_fdf *fdf);
void	init_menu(t_fdf *fdf);

void	update_image(t_fdf *fdf);
void	update_image2(t_fdf *fdf);
void	update_menu(t_fdf *fdf);

t_cam	*init_camera(void);
void	reset_camera(t_fdf *fdf);

void	put_pixel(t_fdf *fdf, int x, int y, int color);
void	draw_line(t_fdf *fdf, t_point *p1, t_point *p2);
int		get_color(t_point *curr, t_point *start, t_point *end, t_point *delta);

void	draw_map(t_fdf *fdf);

void	set_rotation(int keycode, t_fdf *fdf);
void	set_offset(int keycode, t_fdf *fdf);
void	set_projection(int keycode, t_fdf *fdf);

void	transform(t_point *p, t_fdf *fdf);
void	rotate_x(double *y, double *z, double alpha);
void	rotate_y(double *x, double *z, double beta);
void	rotate_z(double *x, double *y, double gamma);

int		key_hook(int keycode, t_fdf *fdf);
int		mouse_hook(int button, int x, int y, t_fdf *fdf);
int		mouse_release_hook(int button, int x, int y, t_fdf *fdf);
int		mouse_move_hook(int x, int y, t_fdf *fdf);
int		render_frame(t_fdf *fdf);

#endif
