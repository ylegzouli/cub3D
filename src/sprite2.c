/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:43:15 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/19 14:29:21 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		calc_dist_sprite(t_sprite **sprite, t_player *player, t_map *map)
{
	t_sprite	*sp;

	sp = *sprite;
	while (sp)
	{
		sp->dist = (player->pos.x - sp->x) * (player->pos.x - sp->x)
			+ (player->pos.y - sp->y) * (player->pos.y - sp->y);
		sp->dist = sqrt(sp->dist);
		sp->size = SIZE_WALL * (map->dist_screen / (sp->dist * SIZE_WALL));
		sp = sp->next;
	}
	sort_sprite(sprite, player);
}

void		sort_sprite(t_sprite **begin, t_player *player)
{
	t_sprite	*sp;
	t_sprite	*bef;
	t_sprite	*nxt;

	sp = *begin;
	bef = 0;
	while (sp->next)
	{
		nxt = sp->next;
		if (sp->dist < nxt->dist)
		{
			swap_sprite(sp, nxt);
			if (bef)
				bef->next = nxt;
			else
				*begin = nxt;
			bef = 0;
			sp = *begin;
		}
		else
		{
			bef = sp;
			sp = sp->next;
		}
	}
}

void		swap_sprite(t_sprite *sp, t_sprite *nxt)
{
	sp->next = nxt->next;
	nxt->next = sp;
}

void		calc_data_spr(t_sprite *spr, t_player *player, t_map *map)
{
	double	sp_x;
	double	sp_y;

	sp_x = spr->x - player->pos.x;
	sp_y = spr->y - player->pos.y;
	spr->inv_det = 1.0 / (player->v0.x * player->v1.y -
	player->v1.x * player->v0.y);
	spr->tmpx = spr->inv_det * (player->v1.y * sp_x - player->v1.x * sp_y);
	spr->tmpy = spr->inv_det * (-player->v0.y * sp_x + player->v0.x * sp_y);
	spr->sx = (map->res_x / 2) * (1 + 1.8 * (spr->tmpx / spr->tmpy));
	spr->start_y = -spr->size / 2 + map->res_y / 2;
	calc_data_spr2(spr, map);
}

void		calc_data_spr2(t_sprite *spr, t_map *map)
{
	if (spr->start_y < 0)
	{
		spr->cuty = -spr->start_y;
		spr->start_y = 0;
	}
	else
		spr->cuty = 0;
	spr->end_y = spr->size / 2 + map->res_y / 2;
	if (spr->end_y >= map->res_y)
		spr->end_y = map->res_y - 1;
	spr->start_x = -spr->size / 2 + spr->sx;
	if (spr->start_x < 0)
	{
		spr->cutx = -spr->start_x;
		spr->start_x = 0;
	}
	else
		spr->cutx = 0;
	spr->end_x = spr->size / 2 + spr->sx;
	if (spr->end_x >= map->res_x)
		spr->end_x = map->res_x - 1;
}
