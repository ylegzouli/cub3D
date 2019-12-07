/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:35:53 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/04 16:02:31 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		raycast(t_map *map, t_player *player, t_raycast **ray, float angle)
{
	(*ray)->tmp_x = player->pos.x * SIZE_WALL;
	(*ray)->tmp_y = player->pos.y * SIZE_WALL;
	inter_x(map, player, ray, angle);
	inter_y(map, player, ray, angle);
	distance_mur(player, ray, angle);
	(*ray)->wall = (SIZE_WALL / (*ray)->dist_wall) * map->dist_screen;
}

void        inter_x(t_map *map, t_player *player, t_raycast **ray, float angle)
{
	int		tmp;
	float	tmp_angle;

	tmp = ((int)((*ray)->tmp_y) / SIZE_WALL);
	if (angle < 180)
	{
        (*ray)->Ya = -SIZE_WALL;
        (*ray)->A.y = tmp * SIZE_WALL - 1;
	}
	else
	{
        (*ray)->Ya = SIZE_WALL;
        (*ray)->A.y = tmp * SIZE_WALL + SIZE_WALL;
    }
	tmp_angle = (angle * 3.14) / 180;
	(*ray)->A.x = (*ray)->tmp_x + ((*ray)->tmp_y - (*ray)->A.y) / tan(tmp_angle);
	(*ray)->Xa = SIZE_WALL / tan(tmp_angle);
	inter_x2(map, ray);
}

void		inter_x2(t_map *map, t_raycast **ray)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = (*ray)->A.x / SIZE_WALL;
	tmp_y = (*ray)->A.y / SIZE_WALL;
	while (tmp_y < map->size_y && tmp_x < map->size_x && (map->map)[tmp_y][tmp_x] != '1')
	{
		(*ray)->A.x = (*ray)->A.x + (*ray)->Xa;
		(*ray)->A.y = (*ray)->A.y + (*ray)->Ya;
		tmp_x = (*ray)->A.x / SIZE_WALL;
		tmp_y = (*ray)->A.y / SIZE_WALL;
	}
}

void		inter_y(t_map *map, t_player *player, t_raycast **ray, float angle)
{
	int		tmp;
	float	tmp_angle;

	tmp = (int)((*ray)->tmp_x / SIZE_WALL);
	if (angle < 270 && angle > 90)
	{
		(*ray)->Xa = -SIZE_WALL;
        (*ray)->B.x = tmp * SIZE_WALL - 1;
	}
	else
    {
        (*ray)->Xa = SIZE_WALL;
        (*ray)->B.x = tmp * SIZE_WALL + SIZE_WALL;
    }
	tmp_angle = (angle * 3.14) / 180;
	(*ray)->B.y = (*ray)->tmp_y + ((*ray)->tmp_x - (*ray)->B.x) * tan(tmp_angle);
	(*ray)->Ya = SIZE_WALL * tan(tmp_angle);
	inter_y2(map, ray);
}

void		inter_y2(t_map *map, t_raycast **ray)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = (int)(*ray)->B.x / SIZE_WALL;
	tmp_y = (int)(*ray)->B.y / SIZE_WALL;
	while (tmp_y < map->size_y && tmp_x < map->size_x && (map->map)[tmp_y][tmp_x] != '1')
	{
		(*ray)->B.x = (*ray)->B.x + (*ray)->Xa;
		(*ray)->B.y = (*ray)->B.y - (*ray)->Ya;
		tmp_x = (int)(*ray)->B.x / SIZE_WALL;
		tmp_y = (int)(*ray)->B.y / SIZE_WALL;
	}
}

void		distance_mur(t_player *player, t_raycast **ray, float angle)
{
	float	dist_A;
	float	dist_B;
	float	tmp_angle;

	tmp_angle = ((angle - player->angle) * 3.14) / 180;
	dist_A = ((*ray)->tmp_x - (*ray)->A.x) * ((*ray)->tmp_x - (*ray)->A.x);
	dist_A = dist_A + ((*ray)->tmp_y - (*ray)->A.y) * ((*ray)->tmp_y - (*ray)->A.y);
	dist_A = sqrt(dist_A);
	dist_B = ((*ray)->tmp_x - (*ray)->B.x) * ((*ray)->tmp_x - (*ray)->B.x);
	dist_B = dist_B + ((*ray)->tmp_y - (*ray)->B.y) * ((*ray)->tmp_y - (*ray)->B.y);
	dist_B = sqrt(dist_B);
	if (dist_B <= dist_A)
	{
//		printf("dist_B\n");
		(*ray)->dist_wall = dist_B * cos(tmp_angle);
	}
	else
	{
//		printf("dist_A\n");
		(*ray)->dist_wall = dist_A * cos(tmp_angle);
	}
}
