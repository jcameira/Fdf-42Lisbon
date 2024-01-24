/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:36:35 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/24 18:35:27 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	end_program(t_vars *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
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

void	move_origin(int keycode, t_vars *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	if (keycode == 65361)
		fdf->map.origin.coordinates[X] -= 10;
	else if (keycode == 65362)
		fdf->map.origin.coordinates[Y] -= 10;
	else if (keycode == 65363)
		fdf->map.origin.coordinates[X] += 10;
	else
		fdf->map.origin.coordinates[Y] += 10;
	draw_map(fdf);
}

void	reset_position(t_vars *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	fdf->map.origin.coordinates[X] = WIDTH / 2;
	fdf->map.origin.coordinates[Y] = HEIGHT / 2;
	draw_map(fdf);
}

void	change_scale(int keycode, t_vars *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	if (keycode == 109)
		fdf->map.scale += 1;
	else
		fdf->map.scale -= 1;
	draw_map(fdf);
}

void	change_z_multiplier(int keycode, t_vars *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	if (keycode == 4)
		fdf->map.z_multiplier += 2;
	else
		fdf->map.z_multiplier -= 2;
	draw_map(fdf);
}

void	map_rotation(int keycode, t_vars *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	if (keycode == 113)
		fdf->map.angles[X]++;
	if (keycode == 101)
		fdf->map.angles[X]--;
	if (keycode == 97)
		fdf->map.angles[Y]++;
	if (keycode == 100)
		fdf->map.angles[Y]--;
	if (keycode == 119)
		fdf->map.angles[Z]++;
	if (keycode == 115)
		fdf->map.angles[Z]--;
	draw_map(fdf);
}

int	key_press(int keycode, t_vars *fdf)
{
	printf("%d\n", keycode);
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
		move_origin(keycode, fdf);
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

	mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	if (prev_x == 0 || prev_y == 0 || !check_vicinity(prev_x, x, prev_y, y))
	{
		prev_x = x;
		prev_y = y;
	}
	if (x != prev_x)
	{
		fdf->map.origin.coordinates[X] -= (prev_x - x) * 10;
		prev_x = x;
	}
	if (y != prev_y)
	{
		fdf->map.origin.coordinates[Y] -= (prev_y - y) * 10;
		prev_y = y;
	}
	draw_map(fdf);
	return (0);
}

int	mouse_press(int button, int x, int y, t_vars *fdf)
{
	x = y;
	if (button == 4 || button == 5)
		change_z_multiplier(button, fdf);
	return (0);
}
