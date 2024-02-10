/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:11:59 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/10 13:12:12 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	matmul(float mat[3][3], t_point point)
{
	int		i;
	int		j;
	t_point	tmp;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		tmp.coordinates[i] = 0;
		while (++j < 3)
		{
			tmp.coordinates[i] += point.coordinates[j] * mat[i][j];
			tmp.color = point.color;
			tmp.paint = point.paint;
		}
	}
	return (tmp);
}

void	rotatex(t_map *map, t_point **projection, int angle)
{
	float	rad;
	int		x;
	int		y;
	float	rotmat[3][3];

	rad = angle * (M_PI / 180);
	rotmat[0][0] = 1;
	rotmat[0][1] = 0;
	rotmat[0][2] = 0;
	rotmat[1][0] = 0;
	rotmat[1][1] = cos(rad);
	rotmat[1][2] = -sin(rad);
	rotmat[2][0] = 0;
	rotmat[2][1] = sin(rad);
	rotmat[2][2] = cos(rad);
	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
			projection[y][x] = matmul(rotmat, projection[y][x]);
	}
}

void	rotatey(t_map *map, t_point **projection, int angle)
{
	float	rad;
	int		x;
	int		y;
	float	rotmat[3][3];

	rad = angle * (M_PI / 180);
	rotmat[0][0] = cos(rad);
	rotmat[0][1] = 0;
	rotmat[0][2] = sin(rad);
	rotmat[1][0] = 0;
	rotmat[1][1] = 1;
	rotmat[1][2] = 0;
	rotmat[2][0] = -sin(rad);
	rotmat[2][1] = 0;
	rotmat[2][2] = cos(rad);
	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
			projection[y][x] = matmul(rotmat, projection[y][x]);
	}
}

void	rotatez(t_map *map, t_point **projection, int angle)
{
	float	rad;
	int		x;
	int		y;
	float	rotmat[3][3];

	rad = angle * (M_PI / 180);
	rotmat[0][0] = cos(rad);
	rotmat[0][1] = -sin(rad);
	rotmat[0][2] = 0;
	rotmat[1][0] = sin(rad);
	rotmat[1][1] = cos(rad);
	rotmat[1][2] = 0;
	rotmat[2][0] = 0;
	rotmat[2][1] = 0;
	rotmat[2][2] = 1;
	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
			projection[y][x] = matmul(rotmat, projection[y][x]);
	}
}

void	orthographic(t_map *map, t_point **projection)
{
	int		x;
	int		y;
	float	rotmat[3][3];

	rotmat[0][0] = 1;
	rotmat[0][1] = 0;
	rotmat[0][2] = 0;
	rotmat[1][0] = 0;
	rotmat[1][1] = 1;
	rotmat[1][2] = 0;
	rotmat[2][0] = 0;
	rotmat[2][1] = 0;
	rotmat[2][2] = 0;
	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
			projection[y][x] = matmul(rotmat, projection[y][x]);
	}
}
