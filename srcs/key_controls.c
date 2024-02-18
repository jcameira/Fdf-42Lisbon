/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:36:35 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/18 00:50:54 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	end_program(t_vars *fdf)
{
	free_map(&fdf->map[fdf->in_use]);
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
}

void	change_prespective(int keycode, t_vars *fdf)
{
	if (keycode == 112)
		fdf->map[fdf->in_use].proj++;
	if (keycode == 111)
		fdf->map[fdf->in_use].proj--;
	if (fdf->map[fdf->in_use].proj > 5)
		fdf->map[fdf->in_use].proj = 0;
	if (fdf->map[fdf->in_use].proj < 0)
		fdf->map[fdf->in_use].proj = 5;
	choose_prespective(fdf, fdf->map[fdf->in_use].proj);
}

void	move_origin(t_vars *fdf)
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

void	keys_origin(int keycode, t_vars *fdf)
{
	if (keycode == 65361)
		fdf->map[fdf->in_use].b_pressed.mov_l = 1;
	else if (keycode == 65362)
		fdf->map[fdf->in_use].b_pressed.mov_u = 1;
	else if (keycode == 65363)
		fdf->map[fdf->in_use].b_pressed.mov_r = 1;
	else
		fdf->map[fdf->in_use].b_pressed.mov_d = 1;
}

void	reset_position(t_vars *fdf)
{
	fdf->map[fdf->in_use].origin.coord[X] = WIDTH / 2;
	fdf->map[fdf->in_use].origin.coord[Y] = HEIGHT / 2;
	fit_window(fdf);
}

void	change_scale(int keycode, t_vars *fdf)
{
	if (keycode == 109 || keycode == 4)
	{
		fdf->map[fdf->in_use].scale += 0.1;
		update_scale_dependants(&fdf->map[fdf->in_use], 0.1, 0);
	}
	else
	{
		fdf->map[fdf->in_use].scale -= 0.1;
		if (fdf->map[fdf->in_use].scale < 1)
		{
			fdf->map[fdf->in_use].scale = 1;
			update_scale_dependants(&fdf->map[fdf->in_use], 0, 1);
		}
		update_scale_dependants(&fdf->map[fdf->in_use], -0.1, 0);
	}
}

void	change_z_mul(int keycode, t_vars *fdf)
{
	if (keycode == 4)
		fdf->map[fdf->in_use].mul[Z] += 0.1;
	else
		fdf->map[fdf->in_use].mul[Z] -= 0.1;
}

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

void	map_rotation(int keycode, t_vars *fdf)
{
	if (keycode == 113)
		fdf->map[fdf->in_use].b_pressed.pos_rot_x = 1;
	if (keycode == 101)
		fdf->map[fdf->in_use].b_pressed.neg_rot_x = 1;
	if (keycode == 97)
		fdf->map[fdf->in_use].b_pressed.pos_rot_y = 1;
	if (keycode == 100)
		fdf->map[fdf->in_use].b_pressed.neg_rot_y = 1;
	if (keycode == 119)
		fdf->map[fdf->in_use].b_pressed.pos_rot_z = 1;
	if (keycode == 115)
		fdf->map[fdf->in_use].b_pressed.neg_rot_z = 1;
}

void	change_mov_vel(int keycode, t_vars *fdf)
{
	if (keycode == 45 && fdf->map[fdf->in_use].t_vel > 0)
		fdf->map[fdf->in_use].t_vel--;
	else
		fdf->map[fdf->in_use].t_vel++;
}

void	change_rot_vel(int keycode, t_vars *fdf)
{
	if (keycode == 91 && fdf->map[fdf->in_use].r_vel > 0)
		fdf->map[fdf->in_use].r_vel--;
	else
		fdf->map[fdf->in_use].r_vel++;
}

void	change_map(t_vars *fdf)
{
	fdf->in_use++;
	if (fdf->in_use > fdf->number_of_maps - 1)
		fdf->in_use = 0;
	fit_window(fdf);
}

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

int	check_vicinity(int x1, int x2, int y1, int y2)
{
	if (abs(x1 - x2) > 10 || abs(y1 - y2) > 10)
		return (0);
	return (1);
}

//void	mouse_l_movement(int x, int y, int prev_x, int prev_y)
//{
//	
//}

int	map_translation(int x, int y, t_vars *fdf)
{
	static int	prev_x;
	static int	prev_y;

	if (prev_x == 0 || prev_y == 0 || !check_vicinity(prev_x, x, prev_y, y))
	{
		prev_x = x;
		prev_y = y;
	}
	if (x != prev_x && fdf->map[fdf->in_use].b_pressed.mouse_l)
	{
		if (fdf->map[fdf->in_use].b_pressed.shift)
			fdf->map[fdf->in_use].angles[X] -= (prev_x - x) * fdf->map[fdf->in_use].r_vel;
		else
			fdf->map[fdf->in_use].origin.coord[X] -= (prev_x - x) * fdf->map[fdf->in_use].t_vel;
	}
	if (y != prev_y && fdf->map[fdf->in_use].b_pressed.mouse_l)
	{
		if (fdf->map[fdf->in_use].b_pressed.shift)
			fdf->map[fdf->in_use].angles[Y] += (prev_y - y) * fdf->map[fdf->in_use].r_vel;
		else
			fdf->map[fdf->in_use].origin.coord[Y] -= (prev_y - y) * fdf->map[fdf->in_use].t_vel;
	}
	if (x != prev_x && fdf->map[fdf->in_use].b_pressed.mouse_r)
		if (fdf->map[fdf->in_use].b_pressed.shift)
			fdf->map[fdf->in_use].angles[Z] -= (prev_x - x) * fdf->map[fdf->in_use].r_vel;
	prev_x = x;
	prev_y = y;
	return (0);
}

int	mouse_release(int button, int x, int y, t_vars *fdf)
{
	x = y;
	y = x;
	if (button == 1)
		fdf->map[fdf->in_use].b_pressed.mouse_l = 0;
	if (button == 3)
		fdf->map[fdf->in_use].b_pressed.mouse_r = 0;
	return (0);
}

int	mouse_press(int button, int x, int y, t_vars *fdf)
{
	if (button == 1)
	{
		if (x > 350 && x < 365 && y > 0 && y < 15 && fdf->menu)
			fdf->menu = 0;
		if (x > 0 && x < 15 && y > 0 && y < 15 && !fdf->menu)
			fdf->menu = 1;
		if (x > 300 && x < 315 && y > 818 && y < 833 && fdf->menu)
			fdf->in_use--;
		if (x > 320 && x < 335 && y > 818 && y < 833 && fdf->menu)
			fdf->in_use++;
		if (fdf->in_use == fdf->number_of_maps)
			fdf->in_use = 0;
		if (fdf->in_use < 0)
			fdf->in_use = fdf->number_of_maps - 1;
		fit_window(fdf);
	}
	if (button == 1)
		fdf->map[fdf->in_use].b_pressed.mouse_l = 1;
	if (button == 3)
		fdf->map[fdf->in_use].b_pressed.mouse_r = 1;
	if (button == 4 || button == 5)
		change_scale(button, fdf);
	return (0);
}

int	render_frame(t_vars *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	move_origin(fdf);
	rotations(fdf);
	if (fdf->menu)
		menu_background(fdf);
	draw_map(fdf);
	if (fdf->menu)
		draw_menu(fdf);
	menu_button(fdf);
	return (0);
}
