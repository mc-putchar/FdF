/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:48:24 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/13 02:42:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ISO_ANGLE	0.523599

void	iso(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(ISO_ANGLE);
	*y = -z + (prev_x + prev_y) * sin(ISO_ANGLE);
}

void	convert_to_iso(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			iso(&fdf->points[y][x]->x, &fdf->points[y][x]->y,
				fdf->points[y][x]->z);
			x++;
		}
		y++;
	}
}

void	set_zoom(t_fdf *fdf, int zoom)
{
	zoom >>= 2;
	if (!zoom)
		zoom = 1;
	if (zoom > 20)
		zoom = 20;
	fdf->zoom = zoom;
}

void	transform(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	*p;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			p = fdf->points[y][x];
			p->x = p->x * fdf->zoom + fdf->offset->x;
			p->y = p->y * fdf->zoom + fdf->offset->y;
			x++;
		}
		y++;
	}
}
