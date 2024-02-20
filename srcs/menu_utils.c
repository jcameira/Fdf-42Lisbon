/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 00:33:51 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/20 12:11:23 by jcameira         ###   ########.fr       */
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

void	string_put_check(t_vars *fdf, int x, int y, char *str)
{
	if (str)
		mlx_string_put(fdf->mlx, fdf->win, x, y, NBR_YELLOW, str);
	else
	{
		ft_printf(ERROR_MAP);
		end_program(fdf, fdf->number_of_maps, 0);
	}
}
