/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 07:48:57 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:28:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, mouse_hook, fdf);
	mlx_hook(fdf->win, 17, 1L << 17, close_window, fdf);
	mlx_loop_hook(fdf->mlx, render_frame, fdf);
}

t_fdf	*init_fdf(char *path)
{
	t_fdf	*fdf;
	t_map	*map;

	map = parse_map(path);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		error_handler(ENOMEM, NULL, free_map, map);
	fdf->map = map;
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		error_handler(MLX_FAIL, "mlx error", free_fdf, fdf);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, TITLE);
	if (!fdf->win)
		error_handler(MLX_FAIL, "mlx error", close_window, fdf);
	fdf->cam = init_camera();
	if (!fdf->cam)
		error_handler(ENOMEM, NULL, close_window, fdf);
	reset_camera(fdf);
	init_img(fdf);
	init_menu(fdf);
	fdf->iso_cos = cos(ISO_ANGLE);
	fdf->iso_sin = sin(ISO_ANGLE);
	return (fdf);
}

void	init_img(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!fdf->img)
		error_handler(MLX_FAIL, "mlx error", close_window, fdf);
	fdf->img_data = malloc(sizeof(t_img_data));
	if (!fdf->img_data)
		error_handler(ENOMEM, NULL, close_window, fdf);
	fdf->img_data->addr = mlx_get_data_addr(fdf->img, \
		&fdf->img_data->bpp, &fdf->img_data->size_line, \
		&fdf->img_data->endian);
	if (!fdf->img_data->addr)
		error_handler(MLX_FAIL, "mlx error", close_window, fdf);
}

void	init_menu(t_fdf *fdf)
{
	fdf->menu = mlx_new_image(fdf->mlx, MENU_WIDTH, MENU_HEIGHT);
	if (!fdf->menu)
		error_handler(MLX_FAIL, "mlx error", close_window, fdf);
	fdf->menu_data = malloc(sizeof(t_img_data));
	if (!fdf->menu_data)
		error_handler(ENOMEM, NULL, close_window, fdf);
	fdf->menu_data->addr = mlx_get_data_addr(fdf->menu, \
		&fdf->menu_data->bpp, &fdf->menu_data->size_line, \
		&fdf->menu_data->endian);
	if (!fdf->menu_data->addr)
		error_handler(MLX_FAIL, "mlx error", close_window, fdf);
	update_menu(fdf);
}
