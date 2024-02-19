/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:45:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/18 20:13:07 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	release_movement(int keycode, t_vars *fdf)
{
	if (keycode == L_ARROW)
		fdf->map[fdf->in_use].b_pressed.mov_l = 0;
	if (keycode == U_ARROW)
		fdf->map[fdf->in_use].b_pressed.mov_u = 0;
	if (keycode == R_ARROW)
		fdf->map[fdf->in_use].b_pressed.mov_r = 0;
	if (keycode == D_ARROW)
		fdf->map[fdf->in_use].b_pressed.mov_d = 0;
	if (keycode == KQ)
		fdf->map[fdf->in_use].b_pressed.pos_rot_x = 0;
	if (keycode == KE)
		fdf->map[fdf->in_use].b_pressed.neg_rot_x = 0;
	if (keycode == KA)
		fdf->map[fdf->in_use].b_pressed.pos_rot_y = 0;
	if (keycode == KD)
		fdf->map[fdf->in_use].b_pressed.neg_rot_y = 0;
	if (keycode == KW)
		fdf->map[fdf->in_use].b_pressed.pos_rot_z = 0;
	if (keycode == KS)
		fdf->map[fdf->in_use].b_pressed.neg_rot_z = 0;
}

void	release_miscelaneous_keys(int keycode, t_vars *fdf)
{
	if (keycode == L_SHIFT)
		fdf->map[fdf->in_use].b_pressed.shift = 0;
	if (keycode == L_CTRL)
		fdf->map[fdf->in_use].b_pressed.ctrl = 0;
	if (keycode == L_ALT)
		fdf->map[fdf->in_use].b_pressed.alt = 0;
}

int	key_release(int keycode, t_vars *fdf)
{
	release_movement(keycode, fdf);
	release_miscelaneous_keys(keycode, fdf);
	return (0);
}
