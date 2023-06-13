/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:43:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/13 00:57:14 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	ft_printf("keycode: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_window(fdf);
	return (EXIT_SUCCESS);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	ft_printf("mouse button: %d, x: %d, y: %d\n", button, x, y);
	if (button == MOUSE_SCROLL_UP)
	{
		set_zoom(fdf, fdf->zoom << 5);
		update_frame(fdf);
		ft_printf("fdf->zoom: %d\n", fdf->zoom);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		set_zoom(fdf, fdf->zoom << 3);
		update_frame(fdf);
	}
	return (EXIT_SUCCESS);
}

int	mouse_release_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)fdf;
	ft_printf("mouse release button: %d, x: %d, y: %d\n", button, x, y);
	return (EXIT_SUCCESS);
}

int	mouse_move_hook(int x, int y, t_fdf *fdf)
{
	(void)fdf;
	ft_printf("mouse move x: %d, y: %d\n", x, y);
	return (EXIT_SUCCESS);
}
