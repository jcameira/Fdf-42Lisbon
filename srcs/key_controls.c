/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:36:35 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/12 01:33:45 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	end_program(t_vars *fdf)
{
	free_map(&fdf->map);
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
}

void	change_prespective(int keycode, t_vars *fdf)
{
	if (keycode == 112)
		fdf->map.projection++;
	if (keycode == 111)
		fdf->map.projection--;
	if (fdf->map.projection > 3)
		fdf->map.projection = 0;
	if (fdf->map.projection < 0)
		fdf->map.projection = 3;
	choose_prespective(fdf, fdf->map.projection);
}

void	move_origin(t_vars *fdf)
{
	if (fdf->map.b_pressed.mov_l)
		fdf->map.origin.coordinates[X] -= fdf->map.translation_velocity;
	if (fdf->map.b_pressed.mov_u)
		fdf->map.origin.coordinates[Y] -= fdf->map.translation_velocity;
	if (fdf->map.b_pressed.mov_r)
		fdf->map.origin.coordinates[X] += fdf->map.translation_velocity;
	if (fdf->map.b_pressed.mov_d)
		fdf->map.origin.coordinates[Y] += fdf->map.translation_velocity;
}

void	keys_origin(int keycode, t_vars *fdf)
{
	if (keycode == 65361)
		fdf->map.b_pressed.mov_l = 1;
	else if (keycode == 65362)
		fdf->map.b_pressed.mov_u = 1;
	else if (keycode == 65363)
		fdf->map.b_pressed.mov_r = 1;
	else
		fdf->map.b_pressed.mov_d = 1;
}

void	reset_position(t_vars *fdf)
{
	fdf->map.origin.coordinates[X] = WIDTH / 2;
	fdf->map.origin.coordinates[Y] = HEIGHT / 2;
}

void	change_scale(int keycode, t_vars *fdf)
{
	if (keycode == 109)
		fdf->map.scale += 0.5;
	else
	{
		fdf->map.scale -= 0.5;
		if (fdf->map.scale < 1)
			fdf->map.scale = 1;
	}
	update_scale_dependants(&fdf->map);
}

void	change_z_multiplier(int keycode, t_vars *fdf)
{
	if (keycode == 4)
		fdf->map.z_multiplier += 2;
	else
		fdf->map.z_multiplier -= 2;
}

void	rotations(t_vars *fdf)
{
	if (fdf->map.b_pressed.pos_rot_x)
		fdf->map.angles[X] += fdf->map.rotation_velocity;
	if (fdf->map.b_pressed.neg_rot_x)
		fdf->map.angles[X] -= fdf->map.rotation_velocity;
	if (fdf->map.b_pressed.pos_rot_y)
		fdf->map.angles[Y] += fdf->map.rotation_velocity;
	if (fdf->map.b_pressed.neg_rot_y)
		fdf->map.angles[Y] -= fdf->map.rotation_velocity;
	if (fdf->map.b_pressed.pos_rot_z)
		fdf->map.angles[Z] += fdf->map.rotation_velocity;
	if (fdf->map.b_pressed.neg_rot_z)
		fdf->map.angles[Z] -= fdf->map.rotation_velocity;
}

void	map_rotation(int keycode, t_vars *fdf)
{
	if (keycode == 113)
		fdf->map.b_pressed.pos_rot_x = 1;
	if (keycode == 101)
		fdf->map.b_pressed.neg_rot_x = 1;
	if (keycode == 97)
		fdf->map.b_pressed.pos_rot_y = 1;
	if (keycode == 100)
		fdf->map.b_pressed.neg_rot_y = 1;
	if (keycode == 119)
		fdf->map.b_pressed.pos_rot_z = 1;
	if (keycode == 115)
		fdf->map.b_pressed.neg_rot_z = 1;
}

void	change_mov_vel(int keycode, t_vars *fdf)
{
	if (keycode == 45 && fdf->map.translation_velocity > 0)
		fdf->map.translation_velocity--;
	else
		fdf->map.translation_velocity++;
}

void	change_rot_vel(int keycode, t_vars *fdf)
{
	if (keycode == 91 && fdf->map.rotation_velocity > 0)
		fdf->map.rotation_velocity--;
	else
		fdf->map.rotation_velocity++;
}

int	key_release(int keycode, t_vars *fdf)
{
	//printf("%d\n", keycode);
	if (keycode == 65361)
		fdf->map.b_pressed.mov_l = 0;
	if (keycode == 65362)
		fdf->map.b_pressed.mov_u = 0;
	if (keycode == 65363)
		fdf->map.b_pressed.mov_r = 0;
	if (keycode == 65364)
		fdf->map.b_pressed.mov_d = 0;
	if (keycode == 113)
		fdf->map.b_pressed.pos_rot_x = 0;
	if (keycode == 101)
		fdf->map.b_pressed.neg_rot_x = 0;
	if (keycode == 97)
		fdf->map.b_pressed.pos_rot_y = 0;
	if (keycode == 100)
		fdf->map.b_pressed.neg_rot_y = 0;
	if (keycode == 119)
		fdf->map.b_pressed.pos_rot_z = 0;
	if (keycode == 115)
		fdf->map.b_pressed.neg_rot_z = 0;
	return (0);
}

int	key_press(int keycode, t_vars *fdf)
{
	if (keycode == 45 || keycode == 61) //-, +
		change_mov_vel(keycode, fdf);
	if (keycode == 91 || keycode == 93) //[, ]
		change_rot_vel(keycode, fdf);
	if (keycode == 113 || keycode == 119 || keycode == 101 || keycode == 97 || keycode == 115 || keycode == 100) //Q, W, E, A, S, D
		map_rotation(keycode, fdf);
	if (keycode == 109 || keycode == 110) //M, N
		change_scale(keycode, fdf);
	if (keycode == 111 || keycode == 112) //O, P
		change_prespective(keycode, fdf);
	if (keycode == 114) //R
		reset_position(fdf);
	if (keycode == 65307) //Esc
		end_program(fdf);
	if (keycode >= 65361 && keycode <= 65364) //Arrows
	{
		//printf("Pressed %d\n", keycode);
		keys_origin(keycode, fdf);
	}
	if (keycode == 103)
		fdf->map.spherical = !fdf->map.spherical;
	return (0);
}

int	check_vicinity(int x1, int x2, int y1, int y2)
{
	if (abs(x1 - x2) > 10 || abs(y1 - y2) > 10)
		return (0);
	return (1);
}

int	map_translation(int x, int y, t_vars *fdf)
{
	static int	prev_x;
	static int	prev_y;

	if (prev_x == 0 || prev_y == 0 || !check_vicinity(prev_x, x, prev_y, y))
	{
		prev_x = x;
		prev_y = y;
	}
	if (x != prev_x)
	{
		fdf->map.origin.coordinates[X] -= (prev_x - x) * fdf->map.translation_velocity;
		prev_x = x;
	}
	if (y != prev_y)
	{
		fdf->map.origin.coordinates[Y] -= (prev_y - y) * fdf->map.translation_velocity;
		prev_y = y;
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_vars *fdf)
{
	x = y;
	y = x;
	if (button == 4 || button == 5)
		change_z_multiplier(button, fdf);
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
	draw_menu(fdf);
	draw_map(fdf);
	return (0);
}
