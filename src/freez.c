/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freez.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:14:56 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:22:34 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(int **matrix, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(matrix[i++]);
	free(matrix);
}

int	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->c_norm)
		free_matrix(map->c_norm, map->height);
	if (map && map->z)
	{
		while (i < map->init)
		{
			free(map->z[i]);
			free(map->c[i++]);
		}
		free(map->z);
		free(map->c);
	}
	free(map);
	return (EXIT_SUCCESS);
}

int	free_arr(char **array)
{
	int	i;

	if (!array)
		return (1);
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (1);
}

int	free_fdf(t_fdf *fdf)
{
	free_map(fdf->map);
	if (fdf->cam)
		free(fdf->cam);
	if (fdf->img)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		free(fdf->img_data);
	}
	if (fdf->menu)
	{
		mlx_destroy_image(fdf->mlx, fdf->menu);
		free(fdf->menu_data);
	}
	if (fdf->win)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
		mlx_destroy_window(fdf->mlx, fdf->win);
	}
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf);
	return (EXIT_SUCCESS);
}
