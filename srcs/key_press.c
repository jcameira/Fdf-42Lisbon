/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:49:07 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/18 00:45:27 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	keyboard_color(int keycode, t_vars *fdf)
{
	if ((keycode >= ONE && keycode <= NINE) || keycode == KI)
		change_color_scheme(fdf, keycode);
	if (keycode == KU)
	{
		turn_negative(fdf);
		fdf->map[fdf->in_use].inverted = !fdf->map[fdf->in_use].inverted;
	}
}

void	keyboard_movement(int keycode, t_vars *fdf)
{
	if (keycode == KQ || keycode == KW || keycode == KE
		|| keycode == KA || keycode == KS || keycode == KD)
		map_rotation(keycode, fdf);
	if (keycode == KR)
		reset_position(fdf);
	if (keycode >= L_ARROW && keycode <= D_ARROW)
		keys_origin(keycode, fdf);
	if (keycode == MINUS || keycode == PLUS)
		change_mov_vel(keycode, fdf);
	if ((keycode == MINUS || keycode == PLUS)
		&& fdf->map[fdf->in_use].b_pressed.shift)
		change_rot_vel(keycode, fdf);
}

void	keyboard_map_change(int keycode, t_vars *fdf)
{
	if (keycode == KN || keycode == KM)
		change_scale(keycode, fdf);
	if (keycode == KO || keycode == KP)
		change_prespective(keycode, fdf);
	if (keycode == KL)
		change_map(fdf);
}

void	key_miscelaneous_buttons(int keycode, t_vars *fdf)
{
	if (keycode == ESC)
		end_program(fdf);
	if (keycode == L_SHIFT)
		fdf->map[fdf->in_use].b_pressed.shift = 1;
}

int	key_press(int keycode, t_vars *fdf)
{
	//printf("Keycode: %d\n", keycode);
	keyboard_movement(keycode, fdf);
	keyboard_color(keycode, fdf);
	keyboard_map_change(keycode, fdf);
	key_miscelaneous_buttons(keycode, fdf);
	return (0);
}
