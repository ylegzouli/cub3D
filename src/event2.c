/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:35:20 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:36:05 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		decal_player2(t_player *player, int key, t_map *map)
{
	double	x;
	double	y;
	double	tmp_x;
	double	tmp_y;
	t_point	v;

	v.x = player->v1.x * cos((-270 * M_PI) / 180) +
	player->v1.y * sin((-270 * M_PI) / 180);
	v.y = (-player->v1.x * sin((-270 * M_PI) / 180) +
	player->v1.y * cos((-270 * M_PI) / 180));
	tmp_x = (player->pos.x * SIZE_WALL) + ((0.3 * v.x) * SIZE_WALL);
	tmp_y = (player->pos.y * SIZE_WALL) + ((0.3 * v.y) * SIZE_WALL);
	x = player->pos.x + 0.3 * v.x;
	y = player->pos.y + 0.3 * v.y;
	if (key == K_D)
	{
		if (map->map[(int)(player->pos.y * SIZE_WALL) /
			SIZE_WALL][(int)tmp_x / SIZE_WALL] != '1')
			player->pos.x = x;
		if (map->map[(int)tmp_y / SIZE_WALL][(int)(player->pos.x * SIZE_WALL)
			/ SIZE_WALL] != '1')
			player->pos.y = y;
	}
}

int			exit_all(t_hook *hook)
{
	mlx_destroy_window(hook->mlx->ptr, hook->mlx->win);
	free(hook->mlx->ptr);
	free(hook->mlx->img);
	free(hook->mlx->cible);
	free(hook->mlx->arme);
	free(hook->mlx->spr_img);
	free(hook->mlx->xpm_img[0]);
	free(hook->mlx->xpm_img[1]);
	free(hook->mlx->xpm_img[2]);
	free(hook->mlx->xpm_img[3]);
	free(hook->mlx);
	free(hook->data);
	free(hook->ray);
	free(hook->map);
	free(hook->player);
	free(hook);
	exit(1);
	return (0);
}
