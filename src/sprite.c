#include "../inc/cub3D.h"

void		init_sprite(t_raycast *ray)
{
	ray->spr = new_sprite(0, 0);
}

t_sprite	*new_sprite(int x, int y)
{
	t_sprite	*new;

	if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
		return (NULL);
	new->x = (double)x + 0.5;
	new->y = (double)y + 0.5;
	new->dist = 0.0;
	new->next = NULL;
	return (new);
}

void			sprite_add_back(t_sprite *spr, int x, int y)
{
	t_sprite	*sp;

	if (!spr)
		spr = new_sprite(x, y);
	else
	{
		sp = spr;
		while (sp->next)
			sp = sp->next;
		sp->next = new_sprite(x, y);
	}
}

void			clear_sprite(t_sprite *begin)
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

void        save_data_spr(t_sprite *sprite, int x, int y)
{
	t_sprite *spr;

	spr = sprite;
	while (spr->next)
		spr = spr->next;
	if (spr->x != x + 0.5 || spr->y != y + 0.5)
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
	sort_sprite(&sprite);
}

void		sort_sprite(t_sprite **sprite)
{
	t_sprite	*sp;
	t_sprite	*bef;
	t_sprite	*nxt;

	if (*sprite)
	{
		sp = *sprite;
		bef = 0;
		while (sp->next)
		{
			nxt = sp->next;
			if (sp->dist < nxt->dist)
			{
				sp->next = nxt->next;
				nxt->next = sp;
				if (bef)
					bef->next = nxt;
				else
					*sprite = nxt;
				sp = *sprite;
			}
			bef = sp;
			sp = sp->next;
		}
	}
}

void        calc_data_spr(t_sprite *spr, t_player *player, t_map *map)
{
	double	sp_x;
	double	sp_y;

	sp_x = spr->x - player->pos.x;
	sp_y = spr->y - player->pos.y;
	spr->inv_det = 1.0 / (player->v0.x * player->v1.y - player->v1.x * player->v0.y);
	spr->tmpx = spr->inv_det * (player->v1.y * sp_x - player->v1.x * sp_y);
	spr->tmpy = spr->inv_det * (-player->v0.y * sp_x + player->v0.x * sp_y);
	spr->sx = (map->res_x / 2) * (1 + spr->tmpx / spr->tmpy);
//	spr->sp_y = abs((int)(map->res_y / spr->tmpy));
	spr->start_y = -spr->size / 2 + map->res_y / 2;// * (map->dist_screen / spr->size);
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
//	spr->sp_x = abs((int)(map->res_y / spr->tmpy));
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
	while (spr)
	{
//		printf("x:%f\ny:%f\ndist:%f\ninvdet:%f\ntmpx:%f\ntmpy:%f\nsx:%d\nsp_x:%d\nsp_y:%d\nstart_y:%d\nend_y:%d\nstart_x:%d\nend_x:%d\n--------------------\n", spr->x,spr->y,spr->dist,spr->inv_det,spr->tmpx,spr->tmpy,spr->sx,spr->sp_x,spr->sp_y,spr->start_y,spr->end_y,spr->start_x,spr->end_x);
		calc_data_spr(spr, player, map);
//		if ((int)player->pos.x != (int)spr->x || (int)player->pos.y != (int)spr->y)
			display_sprite(spr, mlx);
		spr = spr->next;
	}
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
		while (y < spr->end_y)
		{
			color = get_texture_spr(spr, mlx, (x - spr->start_x + spr->cutx), (y - spr->start_y + spr->cuty));
			if (color != 0)
				put_pixel(mlx->img, x, y, color);
			y++;
		}
		x++;
	}
}



