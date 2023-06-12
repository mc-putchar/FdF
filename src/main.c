/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:14:15 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 22:39:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf		fdf;

	if (ac != 2)
	{
		ft_printf("%s\n", USAGE);
		return (EXIT_FAILURE);
	}
	fdf.map = NULL;
	parse_map(av[1], &fdf);
	fdf.window = new_window(WIN_WIDTH, WIN_HEIGHT, "FdF");
	fdf.img = new_image(&fdf, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf.img || get_points(&fdf))
		error_handler(ENOMEM, NULL, close_window, &fdf);
	convert_to_iso(&fdf);
	draw_map(&fdf);
	mlx_put_image_to_window(fdf.window->mlx_ptr, fdf.window->win_ptr,
		fdf.img->img, 0, 0);
	mlx_mouse_hook(fdf.window->win_ptr, mouse_hook, &fdf);
	mlx_hook(fdf.window->win_ptr, 5, 1L << 3, mouse_release_hook, &fdf);
	mlx_hook(fdf.window->win_ptr, 6, 1L << 6, mouse_move_hook, &fdf);
	mlx_hook(fdf.window->win_ptr, 17, 1L << 0, close_window, &fdf);
	mlx_key_hook(fdf.window->win_ptr, key_hook, &fdf);
	mlx_loop(fdf.window->mlx_ptr);
	return (EXIT_SUCCESS);
}
