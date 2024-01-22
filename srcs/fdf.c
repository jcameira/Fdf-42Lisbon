/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:55:13 by joao              #+#    #+#             */
/*   Updated: 2024/01/22 20:55:17 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	*fdf;

	if (argc != 2)
		return (0);
	fdf = vars_init(argv[1]);
	fdf->map = parser(argv[1]);
	draw_map(fdf);
	//mlx_hook(fdf->win, 3, (1L<<1), show_keycode, fdf);
	mlx_hook(fdf->win, 3, (1L<<1), change_prespective, fdf);
	mlx_hook(fdf->win, 3, (1L<<1), end_program, fdf);
	
	mlx_loop(fdf->mlx);
}
