/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:36:08 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 22:35:14 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*new_point(int x, int y, int z, int color)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}

int	get_points(t_fdf *fdf)
{
	t_point	***points;
	int		x;
	int		y;

	points = malloc(sizeof(t_point **) * fdf->map->height);
	if (!points || set_offset(fdf, WIN_WIDTH / 2, 50))
		return (EXIT_FAILURE);
	set_zoom(fdf, lowerof((WIN_WIDTH / (fdf->map->width)), \
		(WIN_HEIGHT / (fdf->map->height))));
	y = -1;
	while (++y < fdf->map->height)
	{
		x = -1;
		points[y] = malloc(sizeof(t_point *) * fdf->map->width);
		if (!points[y])
			return (EXIT_FAILURE);
		while (++x < fdf->map->width)
		{
			points[y][x] = new_point(x * fdf->zoom, y * fdf->zoom, \
			fdf->map->z[y][x], fdf->map->c[y][x]);
			if (!points[y][x])
				return (EXIT_FAILURE);
		}
	}
	fdf->points = points;
	return (EXIT_SUCCESS);
}

void	free_points(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
			free(fdf->points[y][x++]);
		free(fdf->points[y++]);
	}
	free(fdf->points);
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

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	transform(fdf);
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_line(fdf->img, fdf->points[y][x], \
				fdf->points[y][x + 1]);
			if (y < fdf->map->height - 1)
				draw_line(fdf->img, fdf->points[y][x], \
				fdf->points[y + 1][x]);
			x++;
		}
		y++;
	}
}
