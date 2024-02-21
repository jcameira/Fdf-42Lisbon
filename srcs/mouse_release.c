/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_release.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:11:19 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:02:36 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	mouse_release(int button, int x, int y, t_vars *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_L_CLICK)
		fdf->map[fdf->in_use].b_pressed.mouse_l = 0;
	if (button == MOUSE_R_CLICK)
		fdf->map[fdf->in_use].b_pressed.mouse_r = 0;
	return (0);
}
