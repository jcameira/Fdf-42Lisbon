/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:30:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:02:44 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	get_polar_coord(t_map *map)
{
	int		x;
	int		y;
	float	steps_x;
	float	steps_y;

	steps_x = (M_PI * 2) / (map->lim[X] - 1);
	steps_y = M_PI / (map->lim[Y]);
	map->radius = (map->lim[X] * map->scale) / (M_PI * 2);
	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
		{
			map->points[y][x].polar[LONGITUDE] = -(map->points[y][x].coord[X])
				* steps_x;
			map->points[y][x].polar[LATITUDE] = ((map->points[y][x].coord[Y])
					+ (map->lim[Y] / 2)) * steps_y;
		}
	}
}

int	load_coord(t_map *map, t_point ***points, char **z_values, int y)
{
	int		x;
	char	**z_info;

	x = -1;
	while (++x < map->lim[X])
	{
		(*points)[y][x].coord[X] = (x - (map->lim[X] / 2) + 0.5);
		(*points)[y][x].coord[Y] = (y - (map->lim[Y] / 2) + 0.5);
		(*points)[y][x].coord[Z] = (float)atoi(z_values[x]);
		if (ft_strchr(z_values[x], ','))
		{
			z_info = ft_split(z_values[x], ',');
			if (!z_info)
			{
				free_split(z_info);
				return (1);
			}
			(*points)[y][x].original_color = ft_strhextol(z_info[1] + 2);
			free_split(z_info);
		}
		else
			(*points)[y][x].original_color = WHITE;
		(*points)[y][x].color = (*points)[y][x].original_color;
	}
	return (0);
}

t_point	**get_original_points(t_map *map)
{
	int			y;
	char		**z_values;
	t_point		**points;

	points = malloc(sizeof (t_point *) * map->lim[Y]);
	if (!points)
		return (malloc_points_error(map->name));
	y = -1;
	ft_printf("Loading points...\n");
	while (++y < map->lim[Y])
	{
		points[y] = malloc(sizeof (t_point) * map->lim[X]);
		if (!points[y])
			return (read_error(map, points, y, NULL));
		z_values = ft_split(map->map_info[y], ' ');
		if (!z_values)
			return (read_error(map, points, y + 1, NULL));
		if (load_coord(map, &points, z_values, y))
			return (read_error(map, points, y + 1, z_values));
		free_split(z_values);
		print_progress_bar(y + 1, map->lim[Y], map->name);
	}
	ft_printf("\n");
	return (points);
}

char	**read_map(t_map *map, char *file)
{
	int		fd;
	int		y;
	char	**map_info;
	char	*tmp;

	if (fd_check(&fd, file))
		return (NULL);
	map_info = malloc(sizeof (char *) * map->lim[Y]);
	if (!map_info)
		return (malloc_map_error(fd, file));
	tmp = get_next_line(fd);
	y = -1;
	while (++y < map->lim[Y])
	{
		map_info[y] = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!map_info[y])
			return (exit_read_map_early(map_info, fd, file));
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	return (map_info);
}

int	parser(t_map *map, char *file)
{
	map_init(map, file);
	if (get_x_y_limits(map, file))
		return (1);
	map->map_info = read_map(map, file);
	if (!map->map_info)
		return (1);
	map->points = get_original_points(map);
	if (!map->points)
		return (1);
	update_z_limits(map, map->points);
	find_best_z_mul(map);
	get_polar_coord(map);
	return (0);
}
