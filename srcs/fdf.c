/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:55:13 by joao              #+#    #+#             */
/*   Updated: 2024/02/21 02:01:27 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	get_maps(t_vars *fdf, char **argv)
{
	int		i;

	i = -1;
	while (++i < fdf->number_of_maps)
	{
		if (parser(&fdf->map[i], argv[i + 1]))
			end_program(fdf, i, 1);
	}
}

int	main(int argc, char **argv)
{
	t_vars	fdf;

	if (argc < 2)
		return (0);
	fdf.map = input_info_init(&fdf, argc);
	if (!fdf.map)
	{
		ft_printf(ERROR_INIT);
		return (0);
	}
	get_maps(&fdf, argv);
	vars_init(&fdf, "FDF by Jcameira");
	fit_window(&fdf);
	mlx_hook(fdf.win, 2, (1L << 0), key_press, &fdf);
	mlx_hook(fdf.win, 3, (1L << 1), key_release, &fdf);
	mlx_hook(fdf.win, 4, (1L << 2), mouse_press, &fdf);
	mlx_hook(fdf.win, 5, (1L << 3), mouse_release, &fdf);
	mlx_hook(fdf.win, 6, (1L << 6), map_movement, &fdf);
	mlx_hook(fdf.win, 17, 0, exit_button, &fdf);
	mlx_loop_hook(fdf.mlx, render_frame, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
