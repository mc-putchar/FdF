/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:24:38 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 08:26:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char		*dst;

	if (x < 0 || x >= IMG_WIDTH || y < 0 || y >= IMG_HEIGHT)
		return ;
	dst = fdf->img_data->addr + (y * fdf->img_data->size_line + x * \
		(fdf->img_data->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_point	*get_quadrant(t_point *p1, t_point *p2)
{
	t_point	*quad;

	quad = malloc(sizeof(t_point));
	if (!quad)
		return (NULL);
	if (p1->x < p2->x)
		quad->x = 1;
	else
		quad->x = -1;
	if (p1->y < p2->y)
		quad->y = 1;
	else
		quad->y = -1;
	return (quad);
}

static void	get_next_point(t_point *cur, t_point *d, t_point *quad, int e[2])
{
	e[1] = e[0] * 2;
	if (e[1] > -d->y)
	{
		e[0] -= d->y;
		cur->x += quad->x;
	}
	if (e[1] < d->x)
	{
		e[0] += d->x;
		cur->y += quad->y;
	}
}

void	draw_line(t_fdf *fdf, t_point *p1, t_point *p2)
{
	t_point	delta;
	t_point	*quad;
	t_point	cur;
	int		error[2];

	delta.x = ft_abs(p2->x - p1->x);
	delta.y = ft_abs(p2->y - p1->y);
	error[0] = delta.x - delta.y;
	cur = *p1;
	quad = get_quadrant(p1, p2);
	if (!quad)
		return ;
	while (cur.x != p2->x || cur.y != p2->y)
	{
		put_pixel(fdf, cur.x, cur.y, get_color(&cur, p1, p2, &delta));
		get_next_point(&cur, &delta, quad, error);
	}
	put_pixel(fdf, cur.x, cur.y, get_color(&cur, p1, p2, &delta));
	free(quad);
}
