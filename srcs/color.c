/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:07:55 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/16 23:22:28 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	behind_menu(t_point *pixel)
{
	int		new_color[4];
	int		i;

	new_color[T] = (pixel->color >> 24 & 0xFF) - 75;
	new_color[R] = (pixel->color >> 16 & 0xFF) - 75;
	new_color[G] = (pixel->color >> 8 & 0xFF) - 75;
	new_color[B] = (pixel->color & 0xFF) - 75;
	i = -1;
	while (++i < 4)
		if (new_color[i] < 0)
			new_color[i] = 0;
	pixel->color = (new_color[T] << 24) + (new_color[R] << 16)
		+ (new_color[G] << 8) + new_color[B];
}

void	invert_color(t_point *point)
{
	int		new_color[4];
	int		i;

	new_color[T] = -((point->color >> 24 & 0xFF) - 255);
	new_color[R] = -((point->color >> 16 & 0xFF) - 255);
	new_color[G] = -((point->color >> 8 & 0xFF) - 255);
	new_color[B] = -((point->color & 0xFF) - 255);
	i = -1;
	while (++i < 4)
		if (new_color[i] == 0)
			new_color[i] = 1;
	point->color = (new_color[T] << 24) + (new_color[R] << 16)
		+ (new_color[G] << 8) + new_color[B];
}

int	update_color_gradient(int startcolor, int endcolor, float len, float pixels)
{
	float	increment[4];
	int		new_color[4];

	increment[T] = ((endcolor >> 24 & 0xFF) - (startcolor >> 24 & 0xFF)) / len;
	increment[R] = ((endcolor >> 16 & 0xFF) - (startcolor >> 16 & 0xFF)) / len;
	increment[G] = ((endcolor >> 8 & 0xFF) - (startcolor >> 8 & 0xFF)) / len;
	increment[B] = ((endcolor & 0xFF) - (startcolor & 0xFF)) / len;
	new_color[T] = (startcolor >> 24 & 0xFF) + (pixels * increment[T]);
	new_color[R] = (startcolor >> 16 & 0xFF) + (pixels * increment[R]);
	new_color[G] = (startcolor >> 8 & 0xFF) + (pixels * increment[G]);
	new_color[B] = (startcolor & 0xFF) + (pixels * increment[B]);
	return ((new_color[T] << 24) + (new_color[R] << 16)
		+ (new_color[G] << 8) + new_color[B]);
}

void	set_point_color(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
		{
			if (map->points[y][x].coord[Z] > 0 && map->points[y][x].coord[Z] == map->z_max)
				map->points[y][x].color = map->color_scheme.t_color;
			else if (round(map->points[y][x].coord[Z]) == 0)
				map->points[y][x].color = map->color_scheme.m_color;
			else if (map->points[y][x].coord[Z] < 0 && map->points[y][x].coord[Z] == map->z_min)
				map->points[y][x].color = map->color_scheme.b_color;
			else if (map->points[y][x].coord[Z] > 0 && map->points[y][x].coord[Z] / (float)map->z_pos_range >= 0.5)
				map->points[y][x].color = update_color_gradient(map->color_scheme.t_t_color, map->color_scheme.t_color, map->z_pos_range / 2, map->points[y][x].coord[Z] - (map->z_pos_range / 2));
			else if (map->points[y][x].coord[Z] > 0 && map->points[y][x].coord[Z] / (float)map->z_pos_range < 0.5)
				map->points[y][x].color = update_color_gradient(map->color_scheme.m_color, map->color_scheme.t_t_color, map->z_pos_range / 2, map->points[y][x].coord[Z]);
			else if (map->points[y][x].coord[Z] < 0 && (-map->points[y][x].coord[Z]) / (float)map->z_neg_range < 0.5)
				map->points[y][x].color = update_color_gradient(map->color_scheme.m_color, map->color_scheme.b_t_color, map->z_neg_range / 2, (-map->points[y][x].coord[Z]));
			else if (map->points[y][x].coord[Z] < 0 && (-map->points[y][x].coord[Z]) / (float)map->z_neg_range >= 0.5)
				map->points[y][x].color = update_color_gradient(map->color_scheme.b_t_color, map->color_scheme.b_color, map->z_neg_range / 2, (-map->points[y][x].coord[Z]) - (map->z_neg_range / 2));
		}
	}
}

void	get_original_colors(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
			map->points[y][x].color = map->points[y][x].original_color;
	}
}

void	choose_color_scheme(t_map *map)
{
	if (map->scheme == DEFAULT)
	{
		get_original_colors(map);
		return ;
	}
	if (map->scheme == EARTH)
	{
		map->color_scheme.b_color = FULL_BLUE;
		map->color_scheme.b_t_color = DARKISH_AQUA;
		map->color_scheme.m_color = GROUND_GREEN;
		map->color_scheme.t_t_color = SOFT_ORANGE;
		map->color_scheme.t_color = WHITE;
	}
	if (map->scheme == BLUEISH_TONES)
	{
		map->color_scheme.b_color = ALMOST_BLACK;
		map->color_scheme.b_t_color = DEEP_OCEAN;
		map->color_scheme.m_color = GREYISH_BLUE;
		map->color_scheme.t_t_color = GREENISH_GREY;
		map->color_scheme.t_color = ALMOST_WHITE;
	}
	if (map->scheme == SOFTER_TONES)
	{
		map->color_scheme.b_color = DARK_GREY;
		map->color_scheme.b_t_color = GREYISH_GREEN;
		map->color_scheme.m_color = BLUEISH_GREY;
		map->color_scheme.t_t_color = SOFT_PINK;
		map->color_scheme.t_color = EGGSHELL;
	}
	if (map->scheme == BRIGHT_TONES)
	{
		map->color_scheme.b_color = REDISH_GREY;
		map->color_scheme.b_t_color = GREY_BLUE;
		map->color_scheme.m_color = GREY;
		map->color_scheme.t_t_color = ORANGE;
		map->color_scheme.t_color = WHITE;
	}
	if (map->scheme == HIGH_CONTRAST)
	{
		map->color_scheme.b_color = VERY_DARK_BLUE;
		map->color_scheme.b_t_color = BRIGHT_AQUA;
		map->color_scheme.m_color = BRIGHT_RED;
		map->color_scheme.t_t_color = BRIGHT_ORANGE;
		map->color_scheme.t_color = WHITE;
	}
	if (map->scheme == ANOTHER_EARTH)
	{
		map->color_scheme.b_color = MORE_DARK_BLUE;
		map->color_scheme.b_t_color = GREENISH_BLUE;
		map->color_scheme.m_color = BROWN;
		map->color_scheme.t_t_color = BRIGHTER_ORANGE;
		map->color_scheme.t_color = ANOTHER_EGGSHELL;
	}
	if (map->scheme == BRIGHT_PASTEL)
	{
		map->color_scheme.b_color = PASTEL_OCEAN;
		map->color_scheme.b_t_color = PASTEL_AQUA;
		map->color_scheme.m_color = PASTEL_SALMON;
		map->color_scheme.t_t_color = PASTEL_YELLOW;
		map->color_scheme.t_color = PASTEL_ORANGE;
	}
	if (map->scheme == PINKISH_PASTEL)
	{
		map->color_scheme.b_color = MORE_GREYISH_BLUE;
		map->color_scheme.b_t_color = DARK_PURPLE;
		map->color_scheme.m_color = PINKISH_WINE;
		map->color_scheme.t_t_color = PINKISH;
		map->color_scheme.t_color = SOFT_SALMON;
	}
	set_point_color(map);
}
