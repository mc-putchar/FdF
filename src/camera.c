/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 05:42:15 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:30:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cam	*init_camera(void)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	cam->projection = ISOMETRIC;
	return (cam);
}

void	reset_camera(t_fdf *fdf)
{
	if (fdf->map->width > 200 || fdf->map->height > 200)
		fdf->cam->zoom = 5;
	else if (fdf->map->width > 100 || fdf->map->height > 100)
		fdf->cam->zoom = 20;
	else
		fdf->cam->zoom = 40;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->z_divisor = Z_DIVISOR;
	if (fdf->cam->projection == ISOMETRIC)
	{
		fdf->cam->x_offset = IMG_WIDTH >> 1;
		fdf->cam->y_offset = IMG_HEIGHT >> 2;
	}
	else
	{
		fdf->cam->x_offset = 10;
		fdf->cam->y_offset = 10;
	}
}

void	set_rotation(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_A)
		fdf->cam->alpha += ROT_STEP;
	else if (keycode == KEY_S)
		fdf->cam->beta += ROT_STEP;
	else if (keycode == KEY_D)
		fdf->cam->gamma += ROT_STEP;
	else if (keycode == KEY_Q)
		fdf->cam->alpha -= ROT_STEP;
	else if (keycode == KEY_W)
		fdf->cam->beta -= ROT_STEP;
	else if (keycode == KEY_E)
		fdf->cam->gamma -= ROT_STEP;
}

void	set_offset(int keycode, t_fdf *fdf)
{
	if (keycode == ARROW_UP)
		fdf->cam->y_offset -= OFFSET_STEP;
	else if (keycode == ARROW_DOWN)
		fdf->cam->y_offset += OFFSET_STEP;
	else if (keycode == ARROW_LEFT)
		fdf->cam->x_offset -= OFFSET_STEP;
	else if (keycode == ARROW_RIGHT)
		fdf->cam->x_offset += OFFSET_STEP;
}

void	set_projection(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_I)
		fdf->cam->projection = ISOMETRIC;
	else if (keycode == KEY_P)
		fdf->cam->projection = PARALLEL;
	reset_camera(fdf);
}
