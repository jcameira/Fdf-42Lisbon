/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:11:59 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/13 16:36:55 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point matmul(float mat[3][3], t_point point)
{
    int i;
    int j;
    t_point tmp;

    printf("X value pre mul: %f\n", point.coordinates[X]);
    printf("Y value pre mul: %f\n", point.coordinates[Y]);
    printf("Z value pre mul: %f\n", point.coordinates[Z]);
    i = -1;
    while (++i < 3)
    {
        j = -1;
        tmp.coordinates[i] = 0;
        while (++j < 3)
        {
            tmp.coordinates[i] += point.coordinates[j] * mat[i][j];
            printf("Mat vale %d %d: %f\n", i, j, mat[i][j]);
        }
    }
    printf("X value post mul: %f\n", tmp.coordinates[X]);
    printf("Y value post mul: %f\n", tmp.coordinates[Y]);
    printf("Z value post mul: %f\n", tmp.coordinates[Z]);
    return (tmp);
}

void    rotatex(t_map *map, int angle)
{
    int rad;
    int x;
    int y;
    float rotmat[3][3];

    rad = angle * (M_PI/180);
    rotmat[0][0] = 1;
    rotmat[0][1] = 0;
    rotmat[0][2] = 0;
    rotmat[1][0] = 0;
    rotmat[1][1] = cos(rad);
    rotmat[1][2] = -sin(rad);
    rotmat[2][0] = 0;
    rotmat[2][1] = sin(rad);
    rotmat[2][2] = cos(rad);
    y = -1;
    while (++y < map->limits[Y])
    {
        x = -1;
        while (++x < map->limits[X])
        {
            map->points[y][x] = matmul(rotmat, map->points[y][x]);
            printf("X Y Z after x rotation: %f %f %f\n", map->origin->coordinates[X] + map->points[y][x].coordinates[X], map->origin->coordinates[Y] + map->points[y][x].coordinates[Y], map->points[y][x].coordinates[Z]);
        }
    }
}

void    rotatey(t_map *map, int angle)
{
    int rad;
    int x;
    int y;
    float rotmat[3][3];

    rad = angle * (M_PI/180);
    rotmat[0][0] = cos(rad);;
    rotmat[0][1] = 0;
    rotmat[0][2] = sin(rad);
    rotmat[1][0] = 0;
    rotmat[1][1] = 1;
    rotmat[1][2] = 0;
    rotmat[2][0] = -sin(rad);
    rotmat[2][1] = 0;
    rotmat[2][2] = cos(rad);
    y = -1;
    while (++y < map->limits[Y])
    {
        x = -1;
        while (++x < map->limits[X])
            map->points[y][x] = matmul(rotmat, map->points[y][x]);
    }
}

void    rotatez(t_map *map, int angle)
{
    int rad;
    int x;
    int y;
    float rotmat[3][3];

    rad = angle * (M_PI/180);
    rotmat[0][0] = cos(rad);
    rotmat[0][1] = -sin(rad);
    rotmat[0][2] = 0;
    rotmat[1][0] = sin(rad);
    rotmat[1][1] = cos(rad);
    rotmat[1][2] = 0;
    rotmat[2][0] = 0;
    rotmat[2][1] = 0;
    rotmat[2][2] = 1;
    y = -1;
    while (++y < map->limits[Y])
    {
        x = -1;
        while (++x < map->limits[X])
            map->points[y][x] = matmul(rotmat, map->points[y][x]);
    }
}

void    orthographic(t_map *map)
{
    int x;
    int y;
    float rotmat[3][3];

    rotmat[0][0] = 1;
    rotmat[0][1] = 0;
    rotmat[0][2] = 0;
    rotmat[1][0] = 0;
    rotmat[1][1] = 1;
    rotmat[1][2] = 0;
    rotmat[2][0] = 0;
    rotmat[2][1] = 0;
    rotmat[2][2] = 0;
    y = -1;
    while (++y < map->limits[Y])
    {
        x = -1;
        while (++x < map->limits[X])
            map->points[y][x] = matmul(rotmat, map->points[y][x]);
    }
}
