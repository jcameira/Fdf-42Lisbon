/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:07:55 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/20 14:49:57 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_point_color_gradient(t_map *map, int x, int y)
{
	if (map->points[y][x].coord[Z] > 0
		&& map->points[y][x].coord[Z] / (float)map->z_pos_range >= 0.5)
		map->points[y][x].color
			= update_color_gradient(map->color_scheme.t_t_color,
				map->color_scheme.t_color, map->z_pos_range / 2,
				map->points[y][x].coord[Z] - (map->z_pos_range / 2));
	else if (map->points[y][x].coord[Z] > 0
		&& map->points[y][x].coord[Z] / (float)map->z_pos_range < 0.5)
		map->points[y][x].color
			= update_color_gradient(map->color_scheme.m_color,
				map->color_scheme.t_t_color, map->z_pos_range / 2,
				map->points[y][x].coord[Z]);
	else if (map->points[y][x].coord[Z] < 0
		&& (-map->points[y][x].coord[Z]) / (float)map->z_neg_range < 0.5)
		map->points[y][x].color
			= update_color_gradient(map->color_scheme.m_color,
				map->color_scheme.b_t_color, map->z_neg_range / 2,
				(-map->points[y][x].coord[Z]));
	else if (map->points[y][x].coord[Z] < 0
		&& (-map->points[y][x].coord[Z]) / (float)map->z_neg_range >= 0.5)
		map->points[y][x].color
			= update_color_gradient(map->color_scheme.b_t_color,
				map->color_scheme.b_color, map->z_neg_range / 2,
				(-map->points[y][x].coord[Z]) - (map->z_neg_range / 2));
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
			if (map->points[y][x].coord[Z] > 0
				&& ft_round(map->points[y][x].coord[Z]) == map->z_max)
				map->points[y][x].color = map->color_scheme.t_color;
			else if (round(map->points[y][x].coord[Z]) == 0)
				map->points[y][x].color = map->color_scheme.m_color;
			else if (map->points[y][x].coord[Z] < 0
				&& ft_round(map->points[y][x].coord[Z]) == map->z_min)
				map->points[y][x].color = map->color_scheme.b_color;
			else
				set_point_color_gradient(map, x, y);
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

void	choose_extra_schemes(t_map *map)
{
	if (map->scheme == EARTH)
		map->color_scheme = (t_colors){WHITE, SOFT_ORANGE, GROUND_GREEN,
			DARKISH_AQUA, FULL_BLUE};
	if (map->scheme == BLUEISH_TONES)
		map->color_scheme = (t_colors){ALMOST_WHITE, GREENISH_GREY,
			GREYISH_BLUE, DEEP_OCEAN, ALMOST_BLACK};
	if (map->scheme == SOFTER_TONES)
		map->color_scheme = (t_colors){EGGSHELL, SOFT_PINK, BLUEISH_GREY,
			GREYISH_GREEN, DARK_GREY};
	if (map->scheme == BRIGHT_TONES)
		map->color_scheme = (t_colors){WHITE, ORANGE, GREY, GREY_BLUE,
			REDISH_GREY};
	if (map->scheme == HIGH_CONTRAST)
		map->color_scheme = (t_colors){WHITE, BRIGHT_ORANGE, BRIGHT_RED,
			BRIGHT_AQUA, VERY_DARK_BLUE};
	if (map->scheme == ANOTHER_EARTH)
		map->color_scheme = (t_colors){ANOTHER_EGGSHELL, BRIGHTER_ORANGE,
			BROWN, GREENISH_BLUE, MORE_DARK_BLUE};
	if (map->scheme == BRIGHT_PASTEL)
		map->color_scheme = (t_colors){PASTEL_ORANGE, PASTEL_YELLOW,
			PASTEL_SALMON, PASTEL_AQUA, PASTEL_OCEAN};
	if (map->scheme == PINKISH_PASTEL)
		map->color_scheme = (t_colors){SOFT_SALMON, PINKISH, PINKISH_WINE,
			DARK_PURPLE, MORE_GREYISH_BLUE};
}

void	choose_color_scheme(t_map *map)
{
	if (map->scheme == DEFAULT)
	{
		get_original_colors(map);
		return ;
	}
	else
		choose_extra_schemes(map);
	set_point_color(map);
}
