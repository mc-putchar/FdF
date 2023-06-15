/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:31:08 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 12:15:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	free_fdf(fdf);
	exit(EXIT_SUCCESS);
}

void	error_handler(int err, char *str, int (*f)(), void *arg)
{
	int	exit_code;

	exit_code = EXIT_FAILURE;
	if (err <= 0 && str)
		ft_dprintf(STDERR_FILENO, "FdF: %s\n", str);
	else if (str)
		ft_dprintf(STDERR_FILENO, "FdF: %s: %s\n", strerror(err), str);
	else
		ft_dprintf(STDERR_FILENO, "FdF: %s\n", strerror(err));
	if (f)
		(void)(*f)(arg);
	else if (arg)
		free(arg);
	exit(exit_code);
}

int	fgnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
