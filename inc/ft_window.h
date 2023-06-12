/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:59:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 20:23:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WINDOW_H
# define FT_WINDOW_H

# include <mlx.h>
# include <stdlib.h>
# include <errno.h>
# include "error_handler.h"
# include "fdf.h"

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	char	*title;
}	t_window;

struct	s_fdf;

t_window	*new_window(int width, int height, char *title);
int			close_window(struct s_fdf *fdf);

#endif
