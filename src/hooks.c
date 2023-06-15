/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:43:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:30:55 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	else if (keycode == KEY_SPACE)
		reset_camera(fdf);
	else if (keycode == KEY_TAB)
		fdf->cam->z_divisor = Z_DIVISOR;
	else if (keycode >= ARROW_LEFT && keycode <= ARROW_DOWN)
		set_offset(keycode, fdf);
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D || \
	keycode == KEY_Q || keycode == KEY_W || keycode == KEY_E)
		set_rotation(keycode, fdf);
	else if (keycode == KEY_R)
		fdf->cam->z_divisor += 10;
	else if (keycode == KEY_F)
		fdf->cam->z_divisor -= 10;
	else if (keycode == KEY_C)
		fdf->color_mode = !fdf->color_mode;
	else if (keycode == KEY_I || keycode == KEY_P)
		set_projection(keycode, fdf);
	return (EXIT_SUCCESS);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP && fdf->cam->zoom < fdf->map->width * 5)
		fdf->cam->zoom += 1;
	else if (button == MOUSE_SCROLL_DOWN && fdf->cam->zoom > 5)
		fdf->cam->zoom -= 1;
	return (EXIT_SUCCESS);
}

int	render_frame(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, IMG_WIDTH, IMG_HEIGHT);
	fdf->img_data->addr = mlx_get_data_addr(fdf->img, \
		&fdf->img_data->bpp, &fdf->img_data->size_line, \
		&fdf->img_data->endian);
	ft_memset(fdf->img_data->addr, IMG_BG_COLOR, \
	IMG_WIDTH * IMG_HEIGHT * (fdf->img_data->bpp / 8));
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, \
		IMG_X_OFFSET, IMG_Y_OFFSET);
	return (EXIT_SUCCESS);
}
