/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 00:33:51 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/19 01:37:31 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	choose_str_color(t_vars *fdf, int y, char *str, int flag)
{
	if (flag)
		mlx_string_put(fdf->mlx, fdf->win, X_START, y, SELECTION, str);
	else
		mlx_string_put(fdf->mlx, fdf->win, X_START, y, WHITE, str);
}

int	next_line(int *y)
{
	*y += 20;
	return (*y);
}

int	x_end(char *str)
{
	return (X_START + ft_strlen(str) * 6);
}
