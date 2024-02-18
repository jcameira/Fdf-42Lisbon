/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:33:58 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/17 22:34:16 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
