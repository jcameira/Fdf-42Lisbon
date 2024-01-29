/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:30:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/29 13:31:14 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_z_limits(t_map *map, t_point **points)
{
	int	y;
	int	x;

	y = -1;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			if (map->z_min > points[y][x].coordinates[Z])
				map->z_min = points[y][x].coordinates[Z];
			if (map->z_max < points[y][x].coordinates[Z])
				map->z_max = points[y][x].coordinates[Z];
		}
	}
}

void	load_coordinates(t_map *map, t_point ***points, char **z_values, int y)
{
	int	x;

	x = -1;
	while (++x < map->limits[X])
	{
		(*points)[y][x].coordinates[X] = (x - (map->limits[X] / 2) + 0.5);
		(*points)[y][x].coordinates[Y] = (y - (map->limits[Y] / 2) + 0.5);
		(*points)[y][x].coordinates[Z] = (float)atoi(z_values[x]);
		(*points)[y][x].color = 0;
	}
}

t_point	**get_original_points(t_map *map)
{
	int		y;
	char	**z_values;
	t_point	**points;

	points = malloc(sizeof (t_point *) * map->limits[Y]);
	if (!points)
		return (NULL);
	y = -1;
	while (++y < map->limits[Y])
	{
		points[y] = malloc(sizeof (t_point) * map->limits[X]);
		if (!points[y])
			return (NULL);
		z_values = ft_split(map->map_info[y], ' ');
		if (!z_values)
			return (NULL);
		load_coordinates(map, &points, z_values, y);
	}
	return (points);
}

char	**read_map(t_map *map, char *file)
{
	int		fd;
	int		y;
	char	**map_info;

	map_info = malloc(sizeof (char *) * (map->limits[Y] + 1));
	if (!map_info)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	y = -1;
	map_info[++y] = get_next_line(fd);
	while (map_info[y])
	{
		map_info[y] = ft_strtrim(map_info[y], " \n");
		map_info[++y] = get_next_line(fd);
	}
	close(fd);
	return (map_info);
}

void	get_x_y_limits(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	line = ft_strtrim(line, " \n");
	map->limits[X] = (float)word_count(line, ' ');
	map->limits[Y] = 0;
	while (line)
	{
		map->limits[Y]++;
		line = get_next_line(fd);
	}
	free(line);
	printf("X limit: %f\n", map->limits[X]);
	printf("Y limit: %f\n", map->limits[Y]);
	close(fd);
}

void	parser(t_map *map, char *file)
{
	// int		i;
	// int		j;

	map_init(map);
	get_x_y_limits(map, file);
	map->map_info = read_map(map, file);
	map->points = get_original_points(map);
	update_z_limits(map, map->points);
	map->z_range = map->z_max - map->z_min;
	//set_point_color(map);
	// i = -1;
	// while (++i < map->limits[Y])
	// {
	// 	j = -1;
	// 	while (++j < map->limits[X])
	// 	{
	// 		printf("I, J: %d, %d\n", i, j);
	// 		printf("X Y Z: %f %f %f\n", map->points[i][j].coordinates[X], map->points[i][j].coordinates[Y], map->points[i][j].coordinates[Z]);
	// 		printf("Point color: %d\n", map->points[i][j].color);
	// 	}
	// }
	printf("Z_min, Z_max: %d, %d\n", map->z_min, map->z_max);
}
