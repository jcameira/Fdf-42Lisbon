/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/17 00:03:16 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	spherize(t_map *map, t_point **proj)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
		{
			proj[y][x].coord[X] = (map->radius + proj[y][x].coord[Z]) * \
			sin(proj[y][x].polar[LATITUDE]) * cos(proj[y][x].polar[LONGITUDE]);
			proj[y][x].coord[Y] = (map->radius + proj[y][x].coord[Z]) * \
			sin(proj[y][x].polar[LATITUDE]) * sin(proj[y][x].polar[LONGITUDE]);
			proj[y][x].coord[Z] = (map->radius + proj[y][x].coord[Z]) * \
			cos(proj[y][x].polar[LATITUDE]);
		}
	}
	map->proj = SPHERE;
}

void	conic(t_map *map, t_point **proj)
{
	int		x;
	int		y;
	float	rho;
	float	theta;

	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
		{
    		rho = RHO;
    		theta = THETA_LONG;
			proj[y][x].coord[X] = rho * sin(theta);
			proj[y][x].coord[Y] = rho * cos(theta);
		}
	}
	map->proj = CONIC;
}

void	dda_put_pixel(t_vars *fdf, t_point start, t_point end, t_point pixel)
{
	if (start.paint && end.paint && (int)(pixel.coord[X]) <= WIDTH
		&& (int)(pixel.coord[X]) >= 0 && (int)(pixel.coord[Y]) <= HEIGHT
		&& (int)(pixel.coord[Y]) >= 0)
	{
		if ((int)(pixel.coord[X]) <= MENU_WIDTH && (int)(pixel.coord[X]) >= 0
			&& fdf->menu)
			behind_menu(&pixel);
		if ((int)(pixel.coord[X]) <= MENU_WIDTH)
			faster_pixel_put(&fdf->bitmap, (int)(pixel.coord[X]),
				(int)(pixel.coord[Y]), pixel.color);
		else if (*(unsigned int *)(fdf->bitmap.address + ((int)pixel.coord[Y]
				* fdf->bitmap.line_length + (int)pixel.coord[X]
				* (fdf->bitmap.bits_per_pixel / 8)))
				< (unsigned int)pixel.color)
			faster_pixel_put(&fdf->bitmap, (int)(pixel.coord[X]),
				(int)(pixel.coord[Y]), pixel.color);
	}
}

void	dda(t_vars *fdf, t_point start, t_point end)
{
	t_point	pixel;
	int		curr_pixel;
	int		total_pixels;
	float	x_variation;
	float	y_variation;

	if (!inside_window(fdf, start) && !inside_window(fdf, end))
		return ;
	x_variation = end.coord[X] - start.coord[X];
	y_variation = end.coord[Y] - start.coord[Y];
	curr_pixel = sqrt(pow(x_variation, 2) + pow(y_variation, 2));
	total_pixels = curr_pixel;
	x_variation /= curr_pixel;
	y_variation /= curr_pixel;
	pixel.coord[X] = fdf->map[fdf->in_use].origin.coord[X] + start.coord[X];
	pixel.coord[Y] = fdf->map[fdf->in_use].origin.coord[Y] + start.coord[Y];
	while (curr_pixel > 0)
	{
		pixel.color = update_color_gradient(start.color, end.color,
				total_pixels, total_pixels - curr_pixel);
		dda_put_pixel(fdf, start, end, pixel);
		pixel.coord[X] += x_variation;
		pixel.coord[Y] += y_variation;
		curr_pixel--;
	}
}

void	draw_lines(t_vars *fdf, t_point **proj)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map[fdf->in_use].lim[Y])
	{
		x = 0;
		while (x < fdf->map[fdf->in_use].lim[X])
		{
			if (x + fdf->map[fdf->in_use].den
				>= fdf->map[fdf->in_use].lim[X] - 1)
				dda(fdf, proj[y][x], proj[y][fdf->map[fdf->in_use].lim[X] - 1]);
			else
				dda(fdf, proj[y][x], proj[y][x + fdf->map[fdf->in_use].den]);
			if (y + fdf->map[fdf->in_use].den
				>= fdf->map[fdf->in_use].lim[Y] - 1)
				dda(fdf, proj[y][x], proj[fdf->map[fdf->in_use].lim[Y] - 1][x]);
			else
				dda(fdf, proj[y][x], proj[y + fdf->map[fdf->in_use].den][x]);
			x += fdf->map[fdf->in_use].den;
		}
		y += fdf->map[fdf->in_use].den;
	}
}

void	hide_back_sphere(t_map *map, t_point **proj)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
			if (proj[y][x].coord[Z] < 0)
				proj[y][x].paint = 0;
	}
}

void	draw_map(t_vars *fdf)
{
	t_point	**proj;

	proj = copy_map(fdf->map[fdf->in_use]);
	if (fdf->map[fdf->in_use].spherical)
		spherize(&fdf->map[fdf->in_use], proj);
	if (fdf->map[fdf->in_use].conic)
		conic(&fdf->map[fdf->in_use], proj);
	rotatex(&fdf->map[fdf->in_use], proj, fdf->map[fdf->in_use].angles[X]);
	rotatey(&fdf->map[fdf->in_use], proj, fdf->map[fdf->in_use].angles[Y]);
	rotatez(&fdf->map[fdf->in_use], proj, fdf->map[fdf->in_use].angles[Z]);
	if (fdf->map[fdf->in_use].spherical)
		hide_back_sphere(&fdf->map[fdf->in_use], proj);
	orthographic(&fdf->map[fdf->in_use], proj);
	draw_lines(fdf, proj);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap.img, 0, 0);
	free_proj(proj, fdf->map[fdf->in_use]);
}
