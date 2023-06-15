/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:09:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 08:13:01 by mcutura          ###   ########.fr       */
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

static int	get_mix(int start, int end, double percent)
{
	int		red;
	int		green;
	int		blue;

	red = (int)((1 - percent) * (start >> 16 & 0xFF) + \
	percent * (end >> 16 & 0xFF));
	green = (int)((1 - percent) * (start >> 8 & 0xFF) + \
	percent * (end >> 8 & 0xFF));
	blue = (int)((1 - percent) * (start & 0xFF) + \
	percent * (end & 0xFF));
	return ((red << 16) | (green << 8) | blue);
}

int	get_color(t_point *curr, t_point *start, t_point *end, t_point *delta)
{
	double	percent;

	if (start->color == end->color)
		return (end->color);
	if (delta->x > delta->y)
		percent = percent_between(start->x, curr->x, end->x);
	else
		percent = percent_between(start->y, curr->y, end->y);
	return (get_mix(start->color, end->color, percent));
}
