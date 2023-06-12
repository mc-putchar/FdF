/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:09:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 22:25:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	percent_between(int start, int current, int end)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (!distance)
		return (1.0);
	return (placement / distance);
}

static int	get_light(int start, int end, double percent)
{
	return ((int)((1 - percent) * start + percent * end));
}

int	get_color(t_point *current, t_point *start, t_point *end, t_point *delta)
{
	int		red;
	int		green;
	int		blue;
	double	percent;

	if (start->color == end->color)
		return (start->color);
	if (delta->x > delta->y)
		percent = percent_between(start->x, current->x, end->x);
	else
		percent = percent_between(start->y, current->y, end->y);
	red = get_light((start->color >> 16) & 0xFF,
			(end->color >> 16) & 0xFF, percent);
	green = get_light((start->color >> 8) & 0xFF,
			(end->color >> 8) & 0xFF, percent);
	blue = get_light(start->color & 0xFF, end->color & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}
