/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:51:28 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 22:53:38 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_arr(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	set_offset(t_fdf *fdf, int x, int y)
{
	t_point	*p;

	p = new_point(x, y, 0, 0);
	if (!p)
		return (EXIT_FAILURE);
	fdf->offset = p;
	return (EXIT_SUCCESS);
}

int	lowerof(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	greaterof(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
