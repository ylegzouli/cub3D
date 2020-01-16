/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:55:17 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:36:28 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			hook_keydown(int key, t_hook *hook)
{
	if (key == K_LEFT || key == K_RIGHT)
		rotate_player(hook->player, key, 5);
	if (key == K_W || key == K_S)
		move_player(hook->player, key, hook->map);
	if (key == K_A)
		decal_player(hook->player, key, hook->map);
	if (key == K_D)
		decal_player2(hook->player, key, hook->map);
	if (key == K_SPACE)
		hook->player->arme = (hook->player->arme == 0 ? 1 : 0);
	if (key == K_C)
		hook->player->cible = (hook->player->cible == 0 ? 1 : 0);
	if (key == K_M)
		hook->player->map = (hook->player->map == 0 ? 1 : 0);
	if (key == K_ESC)
		return (exit_all(hook));
	affichage(hook->mlx, hook->ray, hook->map, hook->player);
	return (1);
}

void		rotate_player(t_player *player, int key, double angle)
{
	double	x;
	double	y;

	x = player->v1.x;
	y = player->v1.y;
	if (key == K_RIGHT)
	{
		player->v1.x = x * cos((-angle * M_PI) / 180)
		+ y * sin((-angle * M_PI) / 180);
		player->v1.y = (-x * sin((-angle * M_PI) / 180)
		+ y * cos((-angle * M_PI) / 180));
	}
	if (key == K_LEFT)
	{
		player->v1.x = x * cos((angle * M_PI) / 180) +
		y * sin((angle * M_PI) / 180);
		player->v1.y = (-x * sin((angle * M_PI) / 180)) +
		y * cos((angle * M_PI) / 180);
	}
}

void		move_player(t_player *player, int key, t_map *map)
{
	double	x;
	double	y;
	double	tmp_x;
	double	tmp_y;

	tmp_x = (player->pos.x * SIZE_WALL) + ((0.3 * player->v1.x) * SIZE_WALL);
	tmp_y = (player->pos.y * SIZE_WALL) + ((0.3 * player->v1.y) * SIZE_WALL);
	x = player->pos.x + 0.3 * player->v1.x;
	y = player->pos.y + 0.3 * player->v1.y;
	if (key == K_S)
	{
		if (map->map[(int)(player->pos.y * SIZE_WALL) /
			SIZE_WALL][(int)tmp_x / SIZE_WALL] != '1')
			player->pos.x = x;
		if (map->map[(int)tmp_y / SIZE_WALL][(int)(player->pos.x * SIZE_WALL)
			/ SIZE_WALL] != '1')
			player->pos.y = y;
	}
	if (key == K_W)
		move_player2(player, key, map);
}

void		move_player2(t_player *player, int key, t_map *map)
{
	double	x;
	double	y;
	double	tmp_x;
	double	tmp_y;

	tmp_x = (player->pos.x * SIZE_WALL) - ((0.3 * player->v1.x) * SIZE_WALL);
	tmp_y = (player->pos.y * SIZE_WALL) - ((0.3 * player->v1.y) * SIZE_WALL);
	x = player->pos.x - 0.3 * player->v1.x;
	y = player->pos.y - 0.3 * player->v1.y;
	if (map->map[(int)(player->pos.y * SIZE_WALL)
		/ SIZE_WALL][(int)tmp_x / SIZE_WALL] != '1')
		player->pos.x = x;
	if (map->map[(int)tmp_y / SIZE_WALL][(int)(player->pos.x * SIZE_WALL)
		/ SIZE_WALL] != '1')
		player->pos.y = y;
}

void		decal_player(t_player *player, int key, t_map *map)
{
	double	x;
	double	y;
	double	tmp_x;
	double	tmp_y;
	t_point	v;

	v.x = player->v1.x * cos((-90 * M_PI) / 180) +
	player->v1.y * sin((-90 * M_PI) / 180);
	v.y = (-player->v1.x * sin((-90 * M_PI) / 180) +
	player->v1.y * cos((-90 * M_PI) / 180));
	tmp_x = (player->pos.x * SIZE_WALL) + ((0.3 * v.x) * SIZE_WALL);
	tmp_y = (player->pos.y * SIZE_WALL) + ((0.3 * v.y) * SIZE_WALL);
	x = player->pos.x + 0.3 * v.x;
	y = player->pos.y + 0.3 * v.y;
	if (key == K_A)
	{
		if (map->map[(int)(player->pos.y * SIZE_WALL) /
			SIZE_WALL][(int)tmp_x / SIZE_WALL] != '1')
			player->pos.x = x;
		if (map->map[(int)tmp_y / SIZE_WALL][(int)(player->pos.x * SIZE_WALL)
			/ SIZE_WALL] != '1')
			player->pos.y = y;
	}
}
