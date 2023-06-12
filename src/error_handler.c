/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:31:08 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 12:13:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_handler(int err, char *str, int (*f)(), void *arg)
{
	int	exit_code;

	exit_code = EXIT_FAILURE;
	if (str)
		ft_dprintf(STDERR_FILENO, "FdF: %s: %s\n", strerror(err), str);
	else
		ft_dprintf(STDERR_FILENO, "FdF: %s\n", strerror(err));
	if (f)
		exit_code = (*f)(arg);
	else if (arg)
		free(arg);
	exit(exit_code);
}
