/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:11:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 12:13:19 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define LINE_OFF		20
#define CONTROLS_OFFSET	50
#define MAP_INFO_OFFSET	300

void	draw_controls(t_fdf *fdf)
{
	int		x;
	int		y;
	int		k;

	x = MENU_X_OFFSET + 30;
	y = MENU_Y_OFFSET + CONTROLS_OFFSET;
	k = 0;
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
	"###    CONTROLS    ###");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Move:          arrows");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Zoom:          mouse wheel");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Rotate:        WS / AD / QE");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Change height: R / F");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Reset height:  Tab");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Projection:    I / P (iso / parallel)");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Reset camera:  Space");
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
		"Quit:          ESC");
}

void	draw_map_info(t_fdf *fdf)
{
	int		x;
	int		y;
	int		k;
	char	*tmp1;
	char	*tmp2;

	x = MENU_X_OFFSET + 30;
	y = MENU_Y_OFFSET + MAP_INFO_OFFSET;
	k = 0;
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, \
	"###   MAP INFO    ###");
	tmp1 = ft_strjoin("Map name:     ", fdf->map->path);
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, tmp1);
	free(tmp1);
	tmp1 = ft_itoa(fdf->map->width);
	tmp2 = ft_strjoin("Map width:    ", tmp1);
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_itoa(fdf->map->height);
	tmp2 = ft_strjoin("Map height:   ", tmp1);
	mlx_string_put(fdf->mlx, fdf->win, x, y + ++k * LINE_OFF, TXT_COLOR, tmp2);
	free(tmp1);
	free(tmp2);
}

void	draw_menu(t_fdf *fdf)
{
	draw_controls(fdf);
	draw_map_info(fdf);
}

void	update_menu(t_fdf *fdf)
{
	ft_memset(fdf->menu_data->addr, MENU_BG_COLOR, \
		MENU_WIDTH * MENU_HEIGHT * (fdf->menu_data->bpp / 8));
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->menu, \
		MENU_X_OFFSET, MENU_Y_OFFSET);
	draw_menu(fdf);
}
