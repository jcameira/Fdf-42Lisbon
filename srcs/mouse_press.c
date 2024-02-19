/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:10:14 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/19 15:49:50 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_press(int button, int x, int y, t_vars *fdf)
{
	if (button == MOUSE_L_CLICK)
	{
		if (x > 350 && x < 365 && y > 0 && y < 15 && fdf->menu)
			fdf->menu = 0;
		if (x > 0 && x < 15 && y > 0 && y < 15 && !fdf->menu)
			fdf->menu = 1;
		if (x > 300 && x < 315 && y > 958 && y < 973 && fdf->menu)
			fdf->in_use--;
		if (x > 320 && x < 335 && y > 958 && y < 973 && fdf->menu)
			fdf->in_use++;
		if (fdf->in_use == fdf->number_of_maps)
			fdf->in_use = 0;
		if (fdf->in_use < 0)
			fdf->in_use = fdf->number_of_maps - 1;
		fit_window(fdf);
	}
	if (button == MOUSE_L_CLICK)
		fdf->map[fdf->in_use].b_pressed.mouse_l = 1;
	if (button == MOUSE_R_CLICK)
		fdf->map[fdf->in_use].b_pressed.mouse_r = 1;
	if (button == MOUSE_W_UP || button == MOUSE_W_DOWN)
		change_scale(button, fdf);
	return (0);
}
