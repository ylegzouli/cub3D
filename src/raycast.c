/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 09:30:35 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/17 09:30:57 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		get_ray_angle(int x, t_player *player, t_map *map, t_raycast *ray)
{
	ray->angle.x = -((player->v0.x * (x - map->res_x / 2)) + (player->v1.x * map->dist_screen));
	ray->angle.y = -((player->v0.y * (x - map->res_x / 2)) + (player->v1.y * map->dist_screen));
	ray->tan = fabs(ray->angle.y / ray->angle.x);
}

void		raycast(t_map *map, t_player *player, t_raycast **ray)
{
	(*ray)->tmp_x = player->pos.x * SIZE_WALL;
	(*ray)->tmp_y = player->pos.y * SIZE_WALL;
	inter_x(map, ray);
	inter_y(map, ray);
	distance_mur(player, ray);
	(*ray)->wall = (SIZE_WALL / (*ray)->dist_wall) * map->dist_screen;
}

void        inter_x(t_map *map, t_raycast **ray)
{
	int		tmp;

	tmp = ((int)((*ray)->tmp_y) / SIZE_WALL);
	if ((*ray)->angle.y < 0)
	{
        (*ray)->Ya = -SIZE_WALL;
        (*ray)->A.y = tmp * SIZE_WALL - 1;
	}
	else
	{
        (*ray)->Ya = SIZE_WALL;
        (*ray)->A.y = tmp * SIZE_WALL + SIZE_WALL;
    }
	if ((*ray)->angle.x < 0)
	{
		(*ray)->A.x = (*ray)->tmp_x - fabs(((*ray)->tmp_y - (*ray)->A.y) / (*ray)->tan) + 1;
		(*ray)->Xa = -(SIZE_WALL / (*ray)->tan);
	}
	else
	{
		(*ray)->A.x = (*ray)->tmp_x + fabs(((*ray)->tmp_y - (*ray)->A.y) / (*ray)->tan);
		(*ray)->Xa = SIZE_WALL / (*ray)->tan;
	}
	inter_x2(map, ray);
}

void		inter_x2(t_map *map, t_raycast **ray)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = transfer_coords_x(map, (*ray)->A.x);
	tmp_y = transfer_coords_y(map, (*ray)->A.y);
	while (tmp_y < map->size_y && tmp_x < map->size_x && 
		((map->map)[tmp_y][tmp_x] != '1' && (map->map)[tmp_y][tmp_x] != 2))
	{
		(*ray)->A.x = (*ray)->A.x + (*ray)->Xa;
		(*ray)->A.y = (*ray)->A.y + (*ray)->Ya;
		tmp_x = transfer_coords_x(map, (*ray)->A.x);
		tmp_y = transfer_coords_y(map, (*ray)->A.y);
	}
	(*ray)->A.x = (int)((*ray)->A.x);
}

void		inter_y(t_map *map, t_raycast **ray)
{
	int		tmp;

	tmp = (int)((*ray)->tmp_x / SIZE_WALL);
	if ((*ray)->angle.x < 0)
	{
		(*ray)->Xa = -SIZE_WALL;
        (*ray)->B.x = tmp * SIZE_WALL - 1;
	}
	else
    {
        (*ray)->Xa = SIZE_WALL;
        (*ray)->B.x = tmp * SIZE_WALL + SIZE_WALL;
    }
	if ((*ray)->angle.y > 0)
	{
		(*ray)->B.y = (*ray)->tmp_y + fabs(((*ray)->tmp_x - (*ray)->B.x) * (*ray)->tan);
		(*ray)->Ya = -SIZE_WALL * (*ray)->tan;
	}
	else
	{
		(*ray)->B.y = (*ray)->tmp_y - fabs(((*ray)->tmp_x - (*ray)->B.x) * (*ray)->tan) + 1;
		(*ray)->Ya = SIZE_WALL * (*ray)->tan;
	}
	inter_y2(map, ray);
}

void		inter_y2(t_map *map, t_raycast **ray)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = transfer_coords_x(map, (*ray)->B.x);
	tmp_y = transfer_coords_y(map, (*ray)->B.y);
	while (tmp_y < map->size_y && tmp_x < map->size_x 
		&& ((map->map)[tmp_y][tmp_x] != '1' && (map->map)[tmp_y][tmp_x] != 2))
	{
		(*ray)->B.x = (*ray)->B.x + (*ray)->Xa;
		(*ray)->B.y = (*ray)->B.y - (*ray)->Ya;
		tmp_x = transfer_coords_x(map, (*ray)->B.x);
		tmp_y = transfer_coords_y(map, (*ray)->B.y);
	}
	(*ray)->B.y = (int)((*ray)->B.y);
}

void		distance_mur(t_player *player, t_raycast **ray)
{
	double	dist_A;
	double	dist_B;

	dist_A = ((*ray)->tmp_x - (*ray)->A.x) * ((*ray)->tmp_x - (*ray)->A.x);
	dist_A = dist_A + ((*ray)->tmp_y - (*ray)->A.y) * ((*ray)->tmp_y - (*ray)->A.y);
	dist_A = sqrt(dist_A);
	dist_B = ((*ray)->tmp_x - (*ray)->B.x) * ((*ray)->tmp_x - (*ray)->B.x);
	dist_B = dist_B + ((*ray)->tmp_y - (*ray)->B.y) * ((*ray)->tmp_y - (*ray)->B.y);
	dist_B = sqrt(dist_B);
	if (dist_B <= dist_A)
	{
		if ((*ray)->B.x > player->pos.x * SIZE_WALL)
		{
			(*ray)->tex_x = (int)(*ray)->B.y % SIZE_WALL;
			(*ray)->tex = 'E';
		}
		else
		{
			(*ray)->tex_x = (int)(*ray)->B.y % SIZE_WALL;
			(*ray)->tex = 'W';
		}
		(*ray)->dist_wall = dist_B * cos((*ray)->total_angle * M_PI / 180);
	}
	else
	{
		if ((*ray)->A.y < player->pos.y * SIZE_WALL)
		{
			(*ray)->tex_x = (int)(*ray)->A.x % SIZE_WALL;
			(*ray)->tex = 'N';
		}
		else
		{	
			(*ray)->tex_x = (int)(*ray)->A.x % SIZE_WALL;
			(*ray)->tex = 'S';
		}
		(*ray)->dist_wall = dist_A * cos((*ray)->total_angle * M_PI / 180);
	}
// AJOUT GESTION SPRITE !!!
}

int		transfer_coords_x(t_map *map, double x)
{
	int		arr;

	arr = 0;
	if (x > 0 && x < map->size_x * SIZE_WALL)
		arr = ((int)x / SIZE_WALL);
	else if (x >= map->size_x * SIZE_WALL)
		arr = map->size_x - 1;
	return (arr);
}

int		transfer_coords_y(t_map *map, double y)
{
	int		arr;

	arr = 0;
	if (y > 0 && y < map->size_y * SIZE_WALL)
		arr = ((int)y / SIZE_WALL);
	else if (y >= map->size_y * SIZE_WALL)
		arr = map->size_y - 1;
	return (arr);
}
