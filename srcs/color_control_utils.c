/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_control_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:48:47 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/18 18:49:15 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_color_scheme(t_vars *fdf, int keycode)
{
	if (keycode >= ONE && keycode <= NINE)
		fdf->map[fdf->in_use].scheme = keycode - 49;
	choose_color_scheme(&fdf->map[fdf->in_use]);
	if (fdf->map[fdf->in_use].inverted)
		turn_negative(fdf);
}

void	turn_negative(t_vars *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->map[fdf->in_use].lim[Y])
	{
		x = -1;
		while (++x < fdf->map[fdf->in_use].lim[X])
			invert_color(&fdf->map[fdf->in_use].points[y][x]);
	}
}
