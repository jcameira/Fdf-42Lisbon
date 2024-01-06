/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:55:13 by joao              #+#    #+#             */
/*   Updated: 2024/01/05 18:55:16 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vars	*vars_init(char *title)
{
	t_vars		*fdf;

	fdf = malloc(sizeof(t_vars));
	fdf->bitmap = malloc(sizeof(t_bitmap));
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, title);
	fdf->bitmap->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap->address = mlx_get_data_addr(fdf->bitmap->img,
			&fdf->bitmap->bits_per_pixel, &fdf->bitmap->line_length,
			&fdf->bitmap->endian);
	return (fdf);
}

int	main(int argc, char **argv)
{
	t_vars	*fdf;

	if (argc != 2)
		return (0);
	fdf = vars_init(argv[1]);
	
	mlx_loop(fdf->mlx);
}
