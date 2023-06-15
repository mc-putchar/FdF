/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 00:51:19 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 10:20:47 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include <errno.h>
# include <string.h>
# include <stdlib.h>
# define MLX_FAIL	-1
# define EMAPINV	-2

struct	s_fdf;
void	error_handler(int err, char *str, int (*f)(), void *arg);
int		close_window(struct s_fdf *fdf);
int		free_fdf(struct s_fdf *fdf);
int		free_arr(char **array);
int		fgnl(int fd);

#endif
