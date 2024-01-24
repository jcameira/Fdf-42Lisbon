/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:55:13 by joao              #+#    #+#             */
/*   Updated: 2024/01/24 18:15:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	fdf;

	if (argc != 2)
		return (0);
	vars_init(&fdf, argv[1]);
	parser(&fdf.map, argv[1]);
	draw_map(&fdf);
	mlx_hook(fdf.win, 2, (1L << 0), key_press, &fdf);
	mlx_hook(fdf.win, 4, (1L << 2), mouse_press, &fdf);
	mlx_hook(fdf.win, 6, (1L << 8), map_translation, &fdf);
	//mlx_loop_hook(fdf.mlx, );
	mlx_loop(fdf.mlx);
}
