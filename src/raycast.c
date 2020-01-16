/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 09:30:35 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:42:59 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_ray_angle(int x, t_player *player, t_map *map, t_raycast *ray)
{
	ray->angle.x = -((player->v0.x * (x - map->res_x / 2)) +
	(player->v1.x * map->dist_screen));
	ray->angle.y = -((player->v0.y * (x - map->res_x / 2)) +
	(player->v1.y * map->dist_screen));
	ray->tan = fabs(ray->angle.y / ray->angle.x);
}

void	raycast(t_map *map, t_player *player, t_raycast **ray)
{
	(*ray)->tmp_x = player->pos.x * SIZE_WALL;
	(*ray)->tmp_y = player->pos.y * SIZE_WALL;
	inter_x(map, ray);
	inter_y(map, ray);
	distance_mur(player, ray);
	(*ray)->wall = (SIZE_WALL / (*ray)->dist_wall) * map->dist_screen;
}

void	inter_x(t_map *map, t_raycast **ray)
{
	int		tmp;

	tmp = ((int)((*ray)->tmp_y) / SIZE_WALL);
	if ((*ray)->angle.y < 0)
		(*ray)->a.y = tmp * SIZE_WALL - 1;
	else
		(*ray)->a.y = tmp * SIZE_WALL + SIZE_WALL;
	(*ray)->ya = ((*ray)->angle.y < 0 ? -SIZE_WALL : SIZE_WALL);
	if ((*ray)->angle.x < 0)
	{
		(*ray)->a.x = (*ray)->tmp_x - fabs(((*ray)->tmp_y -
		(*ray)->a.y) / (*ray)->tan) + 1;
		(*ray)->xa = -(SIZE_WALL / (*ray)->tan);
	}
	else
	{
		(*ray)->a.x = (*ray)->tmp_x + fabs(((*ray)->tmp_y -
		(*ray)->a.y) / (*ray)->tan);
		(*ray)->xa = SIZE_WALL / (*ray)->tan;
	}
	inter_x2(map, ray);
}

void	inter_x2(t_map *map, t_raycast **ray)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = transfer_coords_x(map, (*ray)->a.x);
	tmp_y = transfer_coords_y(map, (*ray)->a.y);
	while (tmp_y < map->size_y && tmp_x < map->size_x &&
		((map->map)[tmp_y][tmp_x] != '1'))
	{
		if ((map->map)[tmp_y][tmp_x] == '2')
			save_data_spr((*ray)->spr, tmp_x, tmp_y);
		(*ray)->a.x = (*ray)->a.x + (*ray)->xa;
		(*ray)->a.y = (*ray)->a.y + (*ray)->ya;
		tmp_x = transfer_coords_x(map, (*ray)->a.x);
		tmp_y = transfer_coords_y(map, (*ray)->a.y);
	}
	(*ray)->a.x = (int)((*ray)->a.x);
}

void	inter_y(t_map *map, t_raycast **ray)
{
	int		tmp;

	tmp = (int)((*ray)->tmp_x / SIZE_WALL);
	if ((*ray)->angle.x < 0)
		(*ray)->b.x = tmp * SIZE_WALL - 1;
	else
		(*ray)->b.x = tmp * SIZE_WALL + SIZE_WALL;
	(*ray)->xa = ((*ray)->angle.x < 0 ? -SIZE_WALL : SIZE_WALL);
	if ((*ray)->angle.y > 0)
	{
		(*ray)->b.y = (*ray)->tmp_y + fabs(((*ray)->tmp_x -
		(*ray)->b.x) * (*ray)->tan);
		(*ray)->ya = -SIZE_WALL * (*ray)->tan;
	}
	else
	{
		(*ray)->b.y = (*ray)->tmp_y - fabs(((*ray)->tmp_x -
		(*ray)->b.x) * (*ray)->tan) + 1;
		(*ray)->ya = SIZE_WALL * (*ray)->tan;
	}
	inter_y2(map, ray);
}
