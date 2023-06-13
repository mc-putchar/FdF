/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:15:55 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/13 01:02:35 by mcutura          ###   ########.fr       */
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
# include "ft_window.h"
# include "ft_image.h"
# include "keycodes.h"
# include "error_handler.h"

# define USAGE			"usage: ./fdf <filename>"
# define HEX_BASE		"0123456789ABCDEF"
# define WIN_WIDTH		1600
# define WIN_HEIGHT		900
# define DIST			10

struct s_point;
typedef struct s_map
{
	int				width;
	int				height;
	int				**z;
	int				**c;
}	t_map;

struct s_img;
struct s_window;
typedef struct s_fdf
{
	struct s_window	*window;
	struct s_img	*img;
	t_map			*map;
	struct s_point	***points;
	struct s_point	*offset;
	int				zoom;
	int				projection;
}	t_fdf;

void			free_arr(char **array);
int				set_offset(t_fdf *fdf, int x, int y);
int				lowerof(int a, int b);
int				greaterof(int a, int b);

int				parse_map(char *path, t_fdf *fdf);
int				free_map(t_map *map);

void			draw_map(t_fdf *fdf, t_img *img);
struct s_point *new_point(int x, int y, int z, int color);
int				get_points(t_fdf *fdf);
void			free_points(t_fdf *fdf);

void			convert_to_iso(t_fdf *fdf);
void			set_zoom(t_fdf *fdf, int zoom);
void			transform(t_fdf *fdf);

int				get_color(struct s_point *current, struct s_point *start, \
				struct s_point *end, struct s_point *delta);

int				key_hook(int keycode, t_fdf *fdf);
int				mouse_hook(int button, int x, int y, t_fdf *fdf);
int				mouse_release_hook(int button, int x, int y, t_fdf *fdf);
int				mouse_move_hook(int x, int y, t_fdf *fdf);

void			update_frame(t_fdf *fdf);

#endif
