/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   velocity_control_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:21:15 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:02:56 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	change_mov_vel(int keycode, t_vars *fdf)
{
	if (keycode == MINUS && fdf->map[fdf->in_use].t_vel > 0)
		fdf->map[fdf->in_use].t_vel--;
	else if (keycode == PLUS)
		fdf->map[fdf->in_use].t_vel++;
}

void	change_rot_vel(int keycode, t_vars *fdf)
{
	if (keycode == MINUS && fdf->map[fdf->in_use].r_vel > 0)
		fdf->map[fdf->in_use].r_vel--;
	else if (keycode == PLUS)
		fdf->map[fdf->in_use].r_vel++;
}

void	change_scale_vel(int keycode, t_vars *fdf)
{
	if (keycode == MINUS && fdf->map[fdf->in_use].s_vel > 0.1)
		fdf->map[fdf->in_use].s_vel -= 0.1;
	else if (keycode == PLUS)
		fdf->map[fdf->in_use].s_vel += 0.1;
}
