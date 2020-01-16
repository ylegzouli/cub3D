/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:38:59 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:44:01 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_sprite	*new_sprite(int x, int y)
{
	t_sprite	*new;

	if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
		return (NULL);
	new->x = (double)x + 0.5;
	new->y = (double)y + 0.5;
	new->dist = 0;
	new->next = NULL;
	return (new);
}

void		sprite_add_back(t_sprite *spr, int x, int y)
{
	t_sprite	*sp;

	sp = spr;
	while (sp->next)
		sp = sp->next;
	sp->next = new_sprite(x, y);
}

void		clear_sprite(t_sprite *begin)
{
	t_sprite	*sp;
	t_sprite	*next;

	sp = begin;
	while (sp)
	{
		next = sp->next;
		free(sp);
		sp = next;
	}
	begin = NULL;
}

void		print_lst(t_sprite *spr)
{
	while (spr)
	{
		printf("x: %f\ny:%f\ndist: %f\n------------------\n", spr->x, spr->y, spr->dist);
		spr = spr->next;
	}
}

int			is_sprite_save(t_sprite *spr, int x, int y)
{
	while (spr)
	{
		if (spr->x <= (double)x + 0.51 &&
			spr->x >= (double)x + 0.49 &&
			spr->y <= (double)y + 0.51
			&& spr->y >= (double)y + 0.49)
			return (1);
		spr = spr->next;
	}
	return (0);
}

void		save_data_spr(t_sprite *sprite, int x, int y)
{
	if (is_sprite_save(sprite, x, y) == 1)
		return ;
	sprite_add_back(sprite, x, y);
}

void		calc_dist_sprite(t_sprite *sprite, t_player *player, t_map *map)
{
	t_sprite	*sp;

	if (sprite->x == 0.5 && sprite->y == 0.5)
		sprite = sprite->next;
	sp = sprite;
	while (sp)
	{
		sp->dist = (player->pos.x - sp->x) * (player->pos.x - sp->x)
			+ (player->pos.y - sp->y) * (player->pos.y - sp->y);
		sp->dist = sqrt(sp->dist);
		sp->size = SIZE_WALL * (map->dist_screen / (sp->dist * SIZE_WALL));
		sp = sp->next;
	}
//	sort_sprite(&sprite, player);
}

/*
void		sort_sprite(t_sprite **sprite, t_player *player)
{
	t_sprite	*spr;
	t_sprite	*prec;
	t_sprite	*nxt;

	spr = *sprite;
	prec = NULL;
	nxt = spr->next;
	while (nxt)
	{
		prec = spr;
		next =
	}

}
*/
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

void		draw_sprite(t_sprite *spr, t_mlx *mlx, t_player *player, t_map *map)
{
	if (spr->x == 0.5 && spr->y == 0.5)
		spr = spr->next;
//	print_lst(spr);
	while (spr)
	{
		calc_data_spr(spr, player, map);
		display_sprite(spr, mlx);
		spr = spr->next;
	}
//	printf("\n##################\n");
//	printf("\n##################\n");
}

void		display_sprite(t_sprite *spr, t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;

	x = spr->start_x;
	while (x < spr->end_x)
	{
		y = spr->start_y;
		if (mlx->tab[x] > spr->dist * SIZE_WALL)
		{
			while (y < spr->end_y)
			{
				color = get_texture_spr(spr, mlx,
				(x - spr->start_x + spr->cutx), (y - spr->start_y + spr->cuty));
				if (color != 0)
					put_pixel(mlx->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}
