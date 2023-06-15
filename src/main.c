/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:14:15 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 10:31:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
	{
		ft_printf("%s\n", USAGE);
		return (EXIT_FAILURE);
	}
	fdf = init_fdf(av[1]);
	init_hooks(fdf);
	mlx_loop(fdf->mlx);
	return (EXIT_SUCCESS);
}
