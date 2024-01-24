/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:55:13 by joao              #+#    #+#             */
/*   Updated: 2024/01/24 00:29:54 by jcameira         ###   ########.fr       */
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
	//mlx_hook(fdf->win, 2, (1L << 0), show_keycode, fdf);
	mlx_hook(fdf.win, 2, (1L << 0), change_prespective, &fdf);
	//mlx_hook(fdf->win, 2, (1L << 0), end_program, fdf);
	mlx_loop(fdf.mlx);
}
