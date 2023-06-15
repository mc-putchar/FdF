/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:53:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:00:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(double *x, double *y, double z, t_fdf *fdf)
{
	double	prev_y;
	double	prev_x;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * fdf->iso_cos;
	*y = -z + (prev_x + prev_y) * fdf->iso_sin;
}

void	transform(t_point *p, t_fdf *fdf)
{
	double	p_x;
	double	p_y;
	double	p_z;

	p_x = p->x;
	p_y = p->y;
	p_z = p->z;
	p_z *= fdf->cam->zoom;
	if (fdf->cam->projection == ISOMETRIC)
	{
		if (fdf->cam->z_divisor)
			p_z /= fdf->cam->z_divisor;
		iso(&p_x, &p_y, p_z, fdf);
	}
	rotate_x(&p_y, &p_z, fdf->cam->alpha);
	rotate_y(&p_x, &p_z, fdf->cam->beta);
	rotate_z(&p_x, &p_y, fdf->cam->gamma);
	p_x *= fdf->cam->zoom;
	p_y *= fdf->cam->zoom;
	p_x += fdf->cam->x_offset;
	p_y += fdf->cam->y_offset;
	p->x = p_x;
	p->y = p_y;
	p->z = p_z;
}

void	rotate_x(double *y, double *z, double alpha)
{
	double	prev_y;
	double	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(alpha) + prev_z * sin(alpha);
	*z = -prev_y * sin(alpha) + prev_z * cos(alpha);
}

void	rotate_y(double *x, double *z, double beta)
{
	double	prev_x;
	double	prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(beta) + prev_z * sin(beta);
	*z = -prev_x * sin(beta) + prev_z * cos(beta);
}

void	rotate_z(double *x, double *y, double gamma)
{
	double	prev_x;
	double	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(gamma) - prev_y * sin(gamma);
	*y = prev_x * sin(gamma) + prev_y * cos(gamma);
}
