/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:23:46 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:01:22 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	end_program(t_vars *fdf, int maps, int no_vars)
{
	int	i;

	i = -1;
	while (++i < maps)
		free_map(&fdf->map[i]);
	free(fdf->map);
	if (!no_vars)
	{
		mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	exit(0);
}

int	exit_button(t_vars *fdf)
{
	end_program(fdf, fdf->number_of_maps, 0);
	return (0);
}
