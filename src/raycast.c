/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 09:30:35 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:30:54 by ylegzoul         ###   ########.fr       */
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

void	inter_y2(t_map *map, t_raycast **ray)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = transfer_coords_x(map, (*ray)->b.x);
	tmp_y = transfer_coords_y(map, (*ray)->b.y);
	while (tmp_y < map->size_y && tmp_x < map->size_x
		&& ((map->map)[tmp_y][tmp_x] != '1'))
	{
		if ((map->map)[tmp_y][tmp_x] == '2')
			save_data_spr((*ray)->spr, tmp_x, tmp_y);
		(*ray)->b.x = (*ray)->b.x + (*ray)->xa;
		(*ray)->b.y = (*ray)->b.y - (*ray)->ya;
		tmp_x = transfer_coords_x(map, (*ray)->b.x);
		tmp_y = transfer_coords_y(map, (*ray)->b.y);
	}
	(*ray)->b.y = (int)((*ray)->b.y);
}

void	distance_mur(t_player *player, t_raycast **ray)
{
	double	dist_a;
	double	dist_b;

	distance_mur2(&dist_a, &dist_b, ray);
	if (dist_b <= dist_a)
	{
		if ((*ray)->b.x > player->pos.x * SIZE_WALL)
			(*ray)->tex_x = (int)(*ray)->b.y % SIZE_WALL;
		else
			(*ray)->tex_x = (int)(*ray)->b.y % SIZE_WALL;
		(*ray)->tex = ((*ray)->b.x > player->pos.x * SIZE_WALL ? 'E' : 'W');
		(*ray)->dist_wall = dist_b * cos((*ray)->total_angle * M_PI / 180);
	}
	else
	{
		if ((*ray)->a.y < player->pos.y * SIZE_WALL)
			(*ray)->tex_x = (int)(*ray)->a.x % SIZE_WALL;
		else
			(*ray)->tex_x = (int)(*ray)->a.x % SIZE_WALL;
		(*ray)->tex = ((*ray)->a.x < player->pos.y * SIZE_WALL ? 'N' : 'S');
		(*ray)->dist_wall = dist_a * cos((*ray)->total_angle * M_PI / 180);
	}
}

void	distance_mur2(double *dist_a, double *dist_b, t_raycast **ray)
{
	*dist_a = ((*ray)->tmp_x - (*ray)->a.x) * ((*ray)->tmp_x - (*ray)->a.x);
	*dist_a = *dist_a + ((*ray)->tmp_y - (*ray)->a.y) *
	((*ray)->tmp_y - (*ray)->a.y);
	*dist_a = sqrt(*dist_a);
	*dist_b = ((*ray)->tmp_x - (*ray)->b.x) * ((*ray)->tmp_x - (*ray)->b.x);
	*dist_b = *dist_b + ((*ray)->tmp_y - (*ray)->b.y) *
	((*ray)->tmp_y - (*ray)->b.y);
	*dist_b = sqrt(*dist_b);
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
