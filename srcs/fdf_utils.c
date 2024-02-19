/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:39:58 by joao              #+#    #+#             */
/*   Updated: 2024/02/19 20:19:28 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fit_window(t_vars *fdf)
{
	t_point	**proj;
	int		x;
	int		y;

	while (1)
	{
		proj = copy_map(fdf->map[fdf->in_use]);
		if (!proj)
			end_program(fdf, fdf->number_of_maps, 0);
		y = -1;
		while (++y < fdf->map[fdf->in_use].lim[Y])
		{
			x = -1;
			while (++x < fdf->map[fdf->in_use].lim[X])
			{
				if (!inside_window(fdf, proj[y][x]))
				{
					fdf->map[fdf->in_use].f_scale = fdf->map[fdf->in_use].scale;
					free_proj(proj, fdf->map[fdf->in_use]);
					return ;
				}
			}
		}
		fdf->map[fdf->in_use].scale += 0.1;
		update_scale_dependants(&fdf->map[fdf->in_use], 0.1, 0);
		free_proj(proj, fdf->map[fdf->in_use]);
	}
}

int	inside_window(t_vars *fdf, t_point point)
{
	if (fdf->map[fdf->in_use].origin.coord[X] + point.coord[X] >= 0
		&& fdf->map[fdf->in_use].origin.coord[X] + point.coord[X] <= WIDTH)
	{
		if (fdf->map[fdf->in_use].origin.coord[Y] + point.coord[Y] >= 0
			&& fdf->map[fdf->in_use].origin.coord[Y] + point.coord[Y] <= HEIGHT)
		{
			return (1);
		}
	}
	return (0);
}

t_point	**get_proj(t_map original_map)
{
	t_point	**proj;
	int		y;

	proj = malloc(sizeof (t_point *) * original_map.lim[Y]);
	if (!proj)
		return (NULL);
	y = -1;
	while (++y < original_map.lim[Y])
	{
		proj[y] = malloc(sizeof (t_point) * original_map.lim[X]);
		if (!proj[y])
		{
			free_proj(proj, original_map);
			return (NULL);
		}
	}
	return (proj);
}

t_point	**copy_map(t_map original_map)
{
	t_point	**proj;
	int		x;
	int		y;

	proj = get_proj(original_map);
	if (!proj)
		return (NULL);
	y = -1;
	while (++y < original_map.lim[Y])
	{
		x = -1;
		while (++x < original_map.lim[X])
		{
			proj[y][x] = original_map.points[y][x];
			proj[y][x].coord[X] *= original_map.mul[X];
			proj[y][x].coord[Y] *= original_map.mul[Y];
			proj[y][x].coord[Z] *= original_map.mul[Z];
			proj[y][x].color = original_map.points[y][x].color;
			proj[y][x].paint = 1;
		}
	}
	update_z_limits(&original_map, proj);
	return (proj);
}

void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color)
{
	char	*offset;

	offset = bitmap->address + (y * bitmap->line_length
			+ x * (bitmap->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}
