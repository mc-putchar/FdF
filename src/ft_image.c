/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:24:38 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 22:28:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_image.h"

t_img	*new_image(struct s_fdf *fdf, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(fdf->window->mlx_ptr, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, \
		&img->endian);
	img->width = width;
	img->height = height;
	return (img);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
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

void	draw_line(t_img *img, t_point *p1, t_point *p2)
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
		put_pixel(img, cur.x, cur.y, get_color(&cur, p1, p2, &delta));
		get_next_point(&cur, &delta, quad, error);
	}
	free(quad);
}
