/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:54:58 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/18 20:00:34 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_projection(int keycode, t_vars *fdf)
{
	if (keycode == KP)
		fdf->map[fdf->in_use].proj++;
	if (keycode == KO)
		fdf->map[fdf->in_use].proj--;
	if (fdf->map[fdf->in_use].proj > 5)
		fdf->map[fdf->in_use].proj = 0;
	if (fdf->map[fdf->in_use].proj < 0)
		fdf->map[fdf->in_use].proj = 5;
	choose_projection(fdf, fdf->map[fdf->in_use].proj);
}

void	reset_position(t_vars *fdf)
{
	fdf->map[fdf->in_use].origin.coord[X] = WIDTH / 2;
	fdf->map[fdf->in_use].origin.coord[Y] = HEIGHT / 2;
	fdf->map[fdf->in_use].scale = fdf->map[fdf->in_use].f_scale;
	update_scale_dependants(&fdf->map[fdf->in_use],
		fdf->map[fdf->in_use].scale - 1, 1);
}

void	change_map(t_vars *fdf)
{
	fdf->in_use++;
	if (fdf->in_use > fdf->number_of_maps - 1)
		fdf->in_use = 0;
	fit_window(fdf);
}
