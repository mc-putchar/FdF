/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:53:22 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 16:38:44 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"

t_window	*new_window(int width, int height, char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		error_handler(ENOMEM, NULL, NULL, NULL);
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		error_handler(MLX_FAIL, NULL, NULL, window);
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	if (!window->win_ptr)
		error_handler(MLX_FAIL, NULL, NULL, window);
	window->width = width;
	window->height = height;
	window->title = title;
	return (window);
}

int	close_window(struct s_fdf *fdf)
{
	free(fdf->offset);
	if (fdf->points)
		free_points(fdf);
	if (fdf->map)
		free_map(fdf->map);
	mlx_destroy_image(fdf->window->mlx_ptr, fdf->img->img);
	free(fdf->img);
	mlx_destroy_window(fdf->window->mlx_ptr, fdf->window->win_ptr);
	mlx_destroy_display(fdf->window->mlx_ptr);
	free(fdf->window->mlx_ptr);
	free(fdf->window);
	exit(EXIT_SUCCESS);
}
