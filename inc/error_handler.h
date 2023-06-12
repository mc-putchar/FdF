/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 00:51:19 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 12:07:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include <errno.h>
# include <string.h>
# include <stdlib.h>
# define MLX_FAIL	42

void	error_handler(int err, char *str, int (*f)(), void *arg);

#endif
