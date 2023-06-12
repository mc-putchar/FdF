/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:23:36 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 22:02:30 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IMAGE_H
# define FT_IMAGE_H

# include <mlx.h>
# include "error_handler.h"
# include "fdf.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

struct	s_fdf;

t_img	*new_image(struct s_fdf *fdf, int width, int height);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_point *p1, t_point *p2);

#endif
