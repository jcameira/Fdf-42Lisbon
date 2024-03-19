/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:00:11 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/19 17:30:05 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	update_scale_dependants(t_map *map, float increment, int reset)
{
	map->den = 8 / map->scale;
	if (map->den == 0)
		map->den = 1;
	map->radius = (map->lim[X] * map->scale) / (M_PI * 2);
	map->l_vars.major_axis = map->scale
		* ((float)map->lim[X] / (float)20);
	if (reset)
	{
		map->mul[X] = 1;
		map->mul[Y] = 1;
		map->mul[Z] = 1;
	}
	map->mul[X] += increment;
	if (map->mul[X] < 1)
		map->mul[X] = 1;
	map->mul[Y] += increment;
	if (map->mul[Y] < 1)
		map->mul[Y] = 1;
	if (map->z_range < 10)
	{
		map->mul[Z] += increment;
		if (map->mul[Z] < 1)
			map->mul[Z] = 1;
	}
}

void	change_x_mul(int keycode, t_vars *fdf)
{
	if (fdf->map[fdf->in_use].b_pressed.shift)
	{
		if (keycode == KM || keycode == MOUSE_W_UP)
			fdf->map[fdf->in_use].mul[X] += fdf->map[fdf->in_use].s_vel;
		else
			fdf->map[fdf->in_use].mul[X] -= fdf->map[fdf->in_use].s_vel;
	}
}

void	change_y_mul(int keycode, t_vars *fdf)
{
	if (fdf->map[fdf->in_use].b_pressed.ctrl)
	{
		if (keycode == KM || keycode == MOUSE_W_UP)
			fdf->map[fdf->in_use].mul[Y] += fdf->map[fdf->in_use].s_vel;
		else
			fdf->map[fdf->in_use].mul[Y] -= fdf->map[fdf->in_use].s_vel;
	}
}

void	change_z_mul(int keycode, t_vars *fdf)
{
	if (fdf->map[fdf->in_use].b_pressed.alt)
	{
		if (keycode == KM || keycode == MOUSE_W_UP)
			fdf->map[fdf->in_use].mul[Z] += fdf->map[fdf->in_use].s_vel;
		else
			fdf->map[fdf->in_use].mul[Z] -= fdf->map[fdf->in_use].s_vel;
	}
}

void	change_scale(int keycode, t_vars *fdf)
{
	if (fdf->map[fdf->in_use].b_pressed.shift
		|| fdf->map[fdf->in_use].b_pressed.ctrl
		|| fdf->map[fdf->in_use].b_pressed.alt)
	{
		change_x_mul(keycode, fdf);
		change_y_mul(keycode, fdf);
		change_z_mul(keycode, fdf);
	}
	else if (keycode == KM || keycode == MOUSE_W_UP)
	{
		fdf->map[fdf->in_use].scale += fdf->map[fdf->in_use].s_vel;
		update_scale_dependants(&fdf->map[fdf->in_use],
			fdf->map[fdf->in_use].s_vel, 0);
	}
	else if (keycode == KN || keycode == MOUSE_W_DOWN)
	{
		fdf->map[fdf->in_use].scale -= fdf->map[fdf->in_use].s_vel;
		if (fdf->map[fdf->in_use].scale < 1)
		{
			fdf->map[fdf->in_use].scale = 1;
			update_scale_dependants(&fdf->map[fdf->in_use], 0, 1);
		}
		update_scale_dependants(&fdf->map[fdf->in_use],
			-fdf->map[fdf->in_use].s_vel, 0);
	}
}
