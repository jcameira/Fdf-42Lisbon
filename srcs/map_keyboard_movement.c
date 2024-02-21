/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_keyboard_movement.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:31:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:02:08 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	rotations(t_vars *fdf)
{
	if (fdf->map[fdf->in_use].b_pressed.pos_rot_x)
		fdf->map[fdf->in_use].angles[X] += fdf->map[fdf->in_use].r_vel;
	if (fdf->map[fdf->in_use].b_pressed.neg_rot_x)
		fdf->map[fdf->in_use].angles[X] -= fdf->map[fdf->in_use].r_vel;
	if (fdf->map[fdf->in_use].angles[X] > 360
		|| fdf->map[fdf->in_use].angles[X] < -360)
		fdf->map[fdf->in_use].angles[X] = 0;
	if (fdf->map[fdf->in_use].b_pressed.pos_rot_y)
		fdf->map[fdf->in_use].angles[Y] += fdf->map[fdf->in_use].r_vel;
	if (fdf->map[fdf->in_use].b_pressed.neg_rot_y)
		fdf->map[fdf->in_use].angles[Y] -= fdf->map[fdf->in_use].r_vel;
	if (fdf->map[fdf->in_use].angles[Y] > 360
		|| fdf->map[fdf->in_use].angles[Y] < -360)
		fdf->map[fdf->in_use].angles[Y] = 0;
	if (fdf->map[fdf->in_use].b_pressed.pos_rot_z)
		fdf->map[fdf->in_use].angles[Z] += fdf->map[fdf->in_use].r_vel;
	if (fdf->map[fdf->in_use].b_pressed.neg_rot_z)
		fdf->map[fdf->in_use].angles[Z] -= fdf->map[fdf->in_use].r_vel;
	if (fdf->map[fdf->in_use].angles[Z] > 360
		|| fdf->map[fdf->in_use].angles[Z] < -360)
		fdf->map[fdf->in_use].angles[Z] = 0;
}

void	keys_rotation(int keycode, t_vars *fdf)
{
	if (keycode == KQ)
		fdf->map[fdf->in_use].b_pressed.pos_rot_x = 1;
	if (keycode == KE)
		fdf->map[fdf->in_use].b_pressed.neg_rot_x = 1;
	if (keycode == KA)
		fdf->map[fdf->in_use].b_pressed.pos_rot_y = 1;
	if (keycode == KD)
		fdf->map[fdf->in_use].b_pressed.neg_rot_y = 1;
	if (keycode == KW)
		fdf->map[fdf->in_use].b_pressed.pos_rot_z = 1;
	if (keycode == KS)
		fdf->map[fdf->in_use].b_pressed.neg_rot_z = 1;
}

void	translations(t_vars *fdf)
{
	if (fdf->map[fdf->in_use].b_pressed.mov_l)
		fdf->map[fdf->in_use].origin.coord[X] -= fdf->map[fdf->in_use].t_vel;
	if (fdf->map[fdf->in_use].b_pressed.mov_u)
		fdf->map[fdf->in_use].origin.coord[Y] -= fdf->map[fdf->in_use].t_vel;
	if (fdf->map[fdf->in_use].b_pressed.mov_r)
		fdf->map[fdf->in_use].origin.coord[X] += fdf->map[fdf->in_use].t_vel;
	if (fdf->map[fdf->in_use].b_pressed.mov_d)
		fdf->map[fdf->in_use].origin.coord[Y] += fdf->map[fdf->in_use].t_vel;
}

void	keys_translation(int keycode, t_vars *fdf)
{
	if (keycode == L_ARROW)
		fdf->map[fdf->in_use].b_pressed.mov_l = 1;
	else if (keycode == U_ARROW)
		fdf->map[fdf->in_use].b_pressed.mov_u = 1;
	else if (keycode == R_ARROW)
		fdf->map[fdf->in_use].b_pressed.mov_r = 1;
	else
		fdf->map[fdf->in_use].b_pressed.mov_d = 1;
}
