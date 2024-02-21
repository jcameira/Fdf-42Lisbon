/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:07:59 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:01:06 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	behind_menu(t_point *pixel)
{
	int	new_color[3];
	int	i;

	new_color[R] = (pixel->color >> 16 & 0xFF) - 75;
	new_color[G] = (pixel->color >> 8 & 0xFF) - 75;
	new_color[B] = (pixel->color & 0xFF) - 75;
	i = -1;
	while (++i < 3)
		if (new_color[i] < 0)
			new_color[i] = 0;
	pixel->color = (new_color[R] << 16) + (new_color[G] << 8) + new_color[B];
}

void	invert_color(t_point *point)
{
	int		new_color[4];
	int		i;

	new_color[R] = -((point->color >> 16 & 0xFF) - 255);
	new_color[G] = -((point->color >> 8 & 0xFF) - 255);
	new_color[B] = -((point->color & 0xFF) - 255);
	i = -1;
	while (++i < 3)
		if (new_color[i] == 0)
			new_color[i] = 1;
	point->color = (new_color[R] << 16) + (new_color[G] << 8) + new_color[B];
}

int	update_color_gradient(int startcolor, int endcolor, float len, float pixels)
{
	float	increment[3];
	int		new_color[3];

	increment[R] = ((endcolor >> 16 & 0xFF) - (startcolor >> 16 & 0xFF)) / len;
	increment[G] = ((endcolor >> 8 & 0xFF) - (startcolor >> 8 & 0xFF)) / len;
	increment[B] = ((endcolor & 0xFF) - (startcolor & 0xFF)) / len;
	new_color[R] = (startcolor >> 16 & 0xFF) + (pixels * increment[R]);
	new_color[G] = (startcolor >> 8 & 0xFF) + (pixels * increment[G]);
	new_color[B] = (startcolor & 0xFF) + (pixels * increment[B]);
	return ((new_color[R] << 16) + (new_color[G] << 8) + new_color[B]);
}
