/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:55:13 by joao              #+#    #+#             */
/*   Updated: 2024/01/11 12:04:23 by jcameira         ###   ########.fr       */
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
	printf("X limit: %f\n", fdf->map->limits[X]);
	printf("Y limit: %f\n", fdf->map->limits[Y]);
	mlx_loop(fdf->mlx);
}
