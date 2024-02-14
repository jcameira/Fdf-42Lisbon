/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:55:13 by joao              #+#    #+#             */
/*   Updated: 2024/02/14 12:58:04 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	fdf;
	int		i;

	if (argc < 2)
		return (0);
	fdf.map = input_info_init(&fdf, argc);
	i = -1;
	while (++i < fdf.number_of_maps)
		parser(&fdf.map[i], argv[i + 1]);
	vars_init(&fdf, argv[1]);
	fit_window(&fdf);
	mlx_hook(fdf.win, 2, (1L << 0), key_press, &fdf);
	mlx_hook(fdf.win, 3, (1L << 1), key_release, &fdf);
	mlx_hook(fdf.win, 4, (1L << 2), mouse_press, &fdf);
	mlx_hook(fdf.win, 6, (1L << 13), map_translation, &fdf);
	mlx_loop_hook(fdf.mlx, render_frame, &fdf);
	mlx_loop(fdf.mlx);
}
