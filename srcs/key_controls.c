/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:36:35 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/24 00:42:07 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	show_keycode(int keycode, t_vars *fdf)
{
	(void)fdf;
	printf("%d\n", keycode);
	return (0);
}

int	end_program(int keycode, t_vars *fdf)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		exit(0);
	}
	return (0);
}

int	change_prespective(int keycode, t_vars *fdf)
{
	if (keycode == 112)
	{
		fdf->map.projection++;
		if (fdf->map.projection > 1)
			fdf->map.projection = 0;
		choose_prespective(fdf, fdf->map.projection);
	}
	return (0);
}