/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:46:30 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:35:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_limits(t_map *map)
{
	int	i;
	int	j;

	map->z_min = map->z[0][0];
	map->z_max = map->z[0][0];
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->z[i][j] < map->z_min)
				map->z_min = map->z[i][j];
			else if (map->z[i][j] > map->z_max)
				map->z_max = map->z[i][j];
			j++;
		}
		i++;
	}
}

static double	normalize(int z, int min, int max)
{
	double	n;
	double	diff;

	diff = max - min;
	if (!diff)
		return (0);
	n = (z - min) / diff;
	return (n);
}

int	normalize_colors(t_map *map)
{
	int		i;
	int		j;

	map->c_norm = malloc(sizeof(int *) * map->height);
	if (!map->c_norm)
		return (EXIT_FAILURE);
	get_limits(map);
	i = -1;
	while (++i < map->height)
	{
		map->c_norm[i] = malloc(sizeof(int) * map->width);
		if (!map->c_norm[i])
			return (free_matrix(map->c_norm, i), EXIT_FAILURE);
	}
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			map->c_norm[i][j] = 0xFFFF00 * \
			normalize(map->z[i][j], map->z_min, map->z_max) + 0xFF;
	}
	return (EXIT_SUCCESS);
}
