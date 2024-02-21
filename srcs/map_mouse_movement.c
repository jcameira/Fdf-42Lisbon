/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mouse_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:26:41 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:02:10 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	check_vicinity(int x1, int x2, int y1, int y2)
{
	if (abs(x1 - x2) > 10 || abs(y1 - y2) > 10)
		return (0);
	return (1);
}

void	mouse_l_movement(int x, int y, t_vars *fdf)
{
	if (fdf->map[fdf->in_use].b_pressed.shift)
	{
		fdf->map[fdf->in_use].angles[X] -= x
			* fdf->map[fdf->in_use].r_vel;
		fdf->map[fdf->in_use].angles[Y] += y
			* fdf->map[fdf->in_use].r_vel;
	}
	else
	{
		fdf->map[fdf->in_use].origin.coord[X] -= x
			* fdf->map[fdf->in_use].t_vel;
		fdf->map[fdf->in_use].origin.coord[Y] -= y
			* fdf->map[fdf->in_use].t_vel;
	}
}

void	mouse_r_movement(int x, int y, t_vars *fdf)
{
	(void)y;
	if (fdf->map[fdf->in_use].b_pressed.shift)
		fdf->map[fdf->in_use].angles[Z] -= x
			* fdf->map[fdf->in_use].r_vel;
}

int	map_movement(int x, int y, t_vars *fdf)
{
	static int	prev_x;
	static int	prev_y;

	if (!check_vicinity(prev_x, x, prev_y, y))
	{
		prev_x = x;
		prev_y = y;
	}
	if (fdf->map[fdf->in_use].b_pressed.mouse_l)
		mouse_l_movement(prev_x - x, prev_y - y, fdf);
	if (fdf->map[fdf->in_use].b_pressed.mouse_r)
		mouse_r_movement(prev_x - x, prev_y - y, fdf);
	prev_x = x;
	prev_y = y;
	return (0);
}
