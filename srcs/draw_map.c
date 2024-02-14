/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/14 01:13:32 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	spherize(t_map *map, t_point **proj)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			proj[y][x].coord[X] = (map->radius + proj[y][x].coord[Z]) * \
			sin(proj[y][x].polar[LATITUDE]) * cos(proj[y][x].polar[LONGITUDE]);
			proj[y][x].coord[Y] = (map->radius + proj[y][x].coord[Z]) * \
			sin(proj[y][x].polar[LATITUDE]) * sin(proj[y][x].polar[LONGITUDE]);
			proj[y][x].coord[Z] = (map->radius + proj[y][x].coord[Z]) * \
			cos(proj[y][x].polar[LATITUDE]);
		}
	}
}

void	conic(t_map *map, t_point **proj)
{
	int		x;
	int		y;
	float	rho;
	float	theta;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
    		rho = RHO;
    		theta = THETA_LONG;
			proj[y][x].coord[X] = rho * sin(theta);
			proj[y][x].coord[Y] = rho * cos(theta);
		}
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
	pixel.coord[X] = fdf->map.origin.coord[X] + start.coord[X];
	pixel.coord[Y] = fdf->map.origin.coord[Y] + start.coord[Y];
	while (curr_pixel > 0)
	{
		pixel.color = update_color_gradient(start.color, end.color, total_pixels, total_pixels - curr_pixel);	
		if (start.paint && end.paint && (int)(pixel.coord[X]) <= WIDTH && (int)(pixel.coord[X]) >= 0 && (int)(pixel.coord[Y]) <= HEIGHT && (int)(pixel.coord[Y]) >= 0)
		{
			if ((int)(pixel.coord[X]) <= MENU_WIDTH && (int)(pixel.coord[X]) >= 0)
				behind_menu(&pixel);
			faster_pixel_put(&fdf->bitmap, (int)(pixel.coord[X]), (int)(pixel.coord[Y]), pixel.color);
		}
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
	while (y < fdf->map.limits[Y])
	{
		x = 0;
		while (x < fdf->map.limits[X])
		{
			if (x + fdf->map.point_density >= fdf->map.limits[X] - 1)
				dda(fdf, proj[y][x], proj[y][fdf->map.limits[X] - 1]);
			else
				dda(fdf, proj[y][x], proj[y][x + fdf->map.point_density]);
			if (y + fdf->map.point_density >= fdf->map.limits[Y] - 1)
				dda(fdf, proj[y][x], proj[fdf->map.limits[Y] - 1][x]);	
			else
				dda(fdf, proj[y][x], proj[y + fdf->map.point_density][x]);
			x += fdf->map.point_density;
		}
		y += fdf->map.point_density;
	}
}

void	hide_back_sphere(t_map *map, t_point **proj)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
			if (proj[y][x].coord[Z] < 0)
				proj[y][x].paint = 0;
	}
}

void	draw_map(t_vars *fdf)
{
	t_point	**proj;

	proj = copy_map(fdf->map);
	if (fdf->map.spherical)
		spherize(&fdf->map, proj);
	if (fdf->map.conic)
		conic(&fdf->map, proj);
	rotatex(&fdf->map, proj, fdf->map.angles[X]);
	rotatey(&fdf->map, proj, fdf->map.angles[Y]);
	rotatez(&fdf->map, proj, fdf->map.angles[Z]);
	if (fdf->map.spherical)
		hide_back_sphere(&fdf->map, proj);
	orthographic(&fdf->map, proj);
	draw_lines(fdf, proj);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap.img, 0, 0);
	free_proj(proj, fdf->map);
}
