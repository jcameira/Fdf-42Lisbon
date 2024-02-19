/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:30:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/19 03:35:33 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	load_coord(t_map *map, t_point ***points, char **z_values, int y)
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
			(*points)[y][x].original_color = ft_strhextol(z_info[1] + 2);
			free_split(z_info);
		}
		else
			(*points)[y][x].original_color = WHITE;
		(*points)[y][x].color = (*points)[y][x].original_color;
	}
}

void	print_progress_bar(int progress, int total, char *map_name)
{
	int	length;
	int	i;

	length = progress * 50 / total;
	ft_printf("%s [", map_name);
	i = -1;
	while (++i < 50)
	{
		if (i < length)
			ft_printf("#");
		else
			ft_printf("-");
	}
	ft_printf("] %d%%\r", progress * 100 / total);
}

t_point	**get_original_points(t_map *map)
{
	int		y;
	char	**z_values;
	t_point	**points;

	points = malloc(sizeof (t_point *) * map->lim[Y]);
	if (!points)
		return (NULL);
	y = -1;
	while (++y < map->lim[Y])
	{
		points[y] = malloc(sizeof (t_point) * map->lim[X]);
		if (!points[y])
		{
			free_proj(points, *map);
			return (NULL);
		}
		z_values = ft_split(map->map_info[y], ' ');
		if (!z_values)
			return (NULL);
		load_coord(map, &points, z_values, y);
		free_split(z_values);
		print_progress_bar(y + 1, map->lim[Y], map->name);
	}
	printf("\n");
	return (points);
}

char	**read_map(t_map *map, char *file)
{
	int		fd;
	int		y;
	char	**map_info;
	char	*tmp;

	map_info = malloc(sizeof (char *) * map->lim[Y]);
	if (!map_info)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tmp = get_next_line(fd);
	y = -1;
	while (++y < map->lim[Y])
	{
		map_info[y] = ft_strtrim(tmp, " \n");
		if (!map_info[y])
			return (NULL);
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	return (map_info);
}

int	parser(t_map *map, char *file)
{
	static int	read_maps;

	map_init(map, file);
	if (get_x_y_limits(map, file))
	{
		ft_printf("Couldn't read map\n");
		return (1);
	}
	map->map_info = read_map(map, file);
	if (!map->map_info)
	{
		ft_printf("Couldn't read map\n");
		return (1);
	}
	map->points = get_original_points(map);
	if (!map->points)
	{
		ft_printf("Couldn't read map\n");
		return (1);
	}
	update_z_limits(map, map->points);
	find_best_z_mul(map);
	get_polar_coord(map);
	read_maps++;
	return (0);
}
