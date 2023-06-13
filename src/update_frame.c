/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 23:17:33 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/13 00:52:50 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_frame(t_fdf *fdf)
{
	//mlx_clear_window(fdf->window->mlx_ptr, fdf->window->win_ptr);
	draw_map(fdf, fdf->img);
	mlx_put_image_to_window(fdf->window->mlx_ptr, fdf->window->win_ptr,
		fdf->img->img, 0, 0);
}
