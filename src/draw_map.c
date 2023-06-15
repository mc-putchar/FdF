/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:36:08 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:26:53 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_point(t_point *point, int x, int y, t_fdf *fdf)
{
	if (!point)
		return ;
	point->x = x;
	point->y = y;
	point->z = fdf->map->z[y][x];
	if (fdf->color_mode == COLOR_DEFAULT)
		point->color = fdf->map->c[y][x];
	else if (fdf->color_mode == COLOR_HEIGHT)
		point->color = fdf->map->c_norm[y][x];
	transform(point, fdf);
}

void	draw_map(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	curr;
	t_point	next;

	y = -1;
	while (++y < fdf->map->height)
	{
		x = -1;
		while (++x < fdf->map->width)
		{
			set_point(&curr, x, y, fdf);
			if (x < fdf->map->width - 1)
			{
				set_point(&next, x + 1, y, fdf);
				draw_line(fdf, &curr, &next);
			}
			if (y < fdf->map->height - 1)
			{
				set_point(&next, x, y + 1, fdf);
				draw_line(fdf, &curr, &next);
			}
		}
	}
}
