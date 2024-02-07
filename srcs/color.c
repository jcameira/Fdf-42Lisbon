/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:07:55 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/07 21:33:37 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_color_gradient(t_point *start, t_point *end, int pixels)
{
	float	color_increment[4];
	int		updated_color[4];

	color_increment[T] = ((end->color >> 24 & 0xFF) - (start->color >> 24 & 0xFF)) / pixels;
	color_increment[R] = ((end->color >> 16 & 0xFF) - (start->color >> 16 & 0xFF)) / pixels;
	color_increment[G] = ((end->color >> 8 & 0xFF) - (start->color >> 8 & 0xFF)) / pixels;
	color_increment[B] = ((end->color & 0xFF) - (start->color & 0xFF)) / pixels;
	updated_color[T] = (start->color >> 24 & 0xFF) + round(color_increment[T]);
	updated_color[R] = (start->color >> 16 & 0xFF) + round(color_increment[R]);
	updated_color[G] = (start->color >> 8 & 0xFF) + round(color_increment[G]);
	updated_color[B] = (start->color & 0xFF) + round(color_increment[B]);
	start->color = (updated_color[T] << 24) + (updated_color[R] << 16) + (updated_color[G] << 8) + updated_color[B];
}

// void	update_color(t_point *tmp)
// {
// 	int	new_color;

	
// 	printf("Old R: %d\n", tmp->r);
// 	printf("R increment: %f\n", tmp->r_increment);
// 	tmp->r += tmp->r_increment;
// 	printf("New R: %d\n", tmp->r);
// 	tmp->g += tmp->g_increment;
// 	tmp->b += tmp->b_increment;
// 	new_color = tmp->t << 24 | tmp->r << 16 | tmp->g << 8 | tmp->b;
// 	tmp->color = new_color;
// }

// void	set_color_increments(t_point *start, t_point end)
// {
// 	start->t = start->color >> 24 & 0xFF;
// 	start->r = start->color >> 16 & 0xFF;
// 	start->g = start->color >> 8 & 0xFF;
// 	start->b = start->color & 0xFF;
// 	end.r = end.color >> 16 & 0xFF;
// 	end.g = end.color >> 8 & 0xFF;
// 	end.b = end.color & 0xFF;
// 	start->r_increment = (float)(end.r - start->r) / start->nmr_pixels_next_point;
// 	start->g_increment = (float)(end.g - start->g) / start->nmr_pixels_next_point;
// 	start->b_increment = (float)(end.b - start->b) / start->nmr_pixels_next_point;
// }

void	set_point_color(t_map *map, t_point **points)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			if (points[y][x].coordinates[Z] == map->z_max)
				points[y][x].color = WHITE;
			if (points[y][x].coordinates[Z] == map->z_min)
				points[y][x].color = FULL_BLUE;
			if (points[y][x].coordinates[Z] == 0)
				points[y][x].color = FULL_GREEN;
		}
	}
}