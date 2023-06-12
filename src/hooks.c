/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:43:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 16:44:00 by mcutura          ###   ########.fr       */
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
		fdf->zoom += 1;
	else if (button == MOUSE_SCROLL_DOWN)
		fdf->zoom -= 1;
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
