/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:11:59 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/16 23:22:28 by jcameira         ###   ########.fr       */
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
		tmp.coord[i] = 0;
		while (++j < 3)
		{
			tmp.coord[i] += point.coord[j] * mat[i][j];
			tmp.color = point.color;
			tmp.paint = point.paint;
		}
	}
	return (tmp);
}

void	rotatex(t_map *map, t_point **proj, int angle)
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
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
			proj[y][x] = matmul(rotmat, proj[y][x]);
	}
}

void	rotatey(t_map *map, t_point **proj, int angle)
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
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
			proj[y][x] = matmul(rotmat, proj[y][x]);
	}
}

void	rotatez(t_map *map, t_point **proj, int angle)
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
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
			proj[y][x] = matmul(rotmat, proj[y][x]);
	}
}

void	orthographic(t_map *map, t_point **proj)
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
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
			proj[y][x] = matmul(rotmat, proj[y][x]);
	}
}
