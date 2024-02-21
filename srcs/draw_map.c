/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:01:18 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
			map->l_vars.theta_long = map->l_vars.parallel_median
				* (proj[y][x].polar[LONGITUDE] - map->l_vars.meridian);
			map->l_vars.theta_lat = map->l_vars.parallel_median
				* (proj[y][x].polar[LATITUDE] - map->l_vars.origin_lat);
			rho = map->l_vars.major_axis * sqrt(map->l_vars.radial_distance)
				/ map->l_vars.parallel_median * tan(M_PI / 4
					- map->l_vars.theta_lat / 2);
			theta = map->l_vars.theta_long;
			proj[y][x].coord[X] = rho * sin(theta);
			proj[y][x].coord[Y] = rho * cos(theta);
		}
	}
	map->proj = CONIC;
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

void	draw_map(t_vars *fdf)
{
	t_point	**proj;

	proj = copy_map(fdf->map[fdf->in_use]);
	if (!proj)
		return ;
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
	free_proj(proj, fdf->map[fdf->in_use].lim[Y]);
}
