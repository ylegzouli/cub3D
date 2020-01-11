/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:16:40 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/11 19:16:00 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void		draw_sprite(t_mlx *mlx, t_raycast *ray)
{
	int		i;

	i = ray->nb_sprite - 1;
	while (i >= 0)
	{
		display_sprite(mlx, ray->spr[i], ray);
		i--;
	}
}

void		init_sprite(t_raycast *ray)
{
	int		i;

	i = 0;
	ray->nb_sprite = 0;
	ray->dist_spr = 0;
	while (i < 99)
	{
		ray->spr[i] = malloc(sizeof(t_sprite));
		ray->spr[i]->sx = 0;
		ray->spr[i]->sy = 0;
		ray->spr[i]->mapx = 0;
		ray->spr[i]->mapy = 0;
		ray->spr[i]->dist = 0;
		ray->spr[i]->size = 0;
		ray->spr[i]->imgx = 0;
		ray->spr[i]->imgy = 0;
		ray->spr[i]->color = 0;

		ray->start = -1;
		ray->spr[i]->start = 0;
		ray->spr[i]->xmax = 0;
		
		i++;
	}
}

void		save_data_spr(t_raycast *ray, t_map *map, int x, int y)
{
	int		i;

	i = ray->nb_sprite;
	if (i == 0 || (ray->spr[i - 1]->mapx != x && ray->spr[i - 1]->mapy != y))
	{
		ray->spr[i]->size = size_spr(ray, map);
		ray->spr[i]->dist = ray->dist_spr;
		ray->spr[i]->mapx = x;
		ray->spr[i]->mapy = y;
		ray->spr[i]->xmax = 1;
		ray->nb_sprite++;
	}
	else if (ray->spr[i - 1]->mapx == x && ray->spr[i - 1]->mapy == y)
		(ray->spr[i - 1]->xmax)++;
}

void		save_pos_spr(t_raycast *ray, int x, t_map *map)
{
	int		i;

	i = ray->nb_sprite;
	if (i != 0 && ray->spr[i - 1]->sx != x && !(ray->spr[i - 1]->sx))
	{
		ray->spr[i - 1]->sx = x;
		ray->spr[i - 1]->sy = (HAUTEUR_SCREEN / 2) - 32 * (map->dist_screen / ray->dist_spr);
	}
	else if (i == 0 && ray->spr[i]->mapx != 0)
	{
		ray->spr[i]->sx = x;
		ray->spr[i - 1]->sy = (HAUTEUR_SCREEN / 2) - 32 * (map->dist_screen / ray->dist_spr);
	}
}

void		display_sprite(t_mlx *mlx, t_sprite *spr, t_raycast *ray)
{
	int		x;
	int		y;

	x = 0;
//	x = spr->start;;
//	printf("start:%d\nmax:%d\nsize:%f\nspr_sx:%d\nspr_sy:%d\n", spr->start, spr->xmax, spr->size, spr->sx, spr->sy);
	while (x < spr->xmax)
	{
		y = 0;
		while (y < spr->size)
		{
			spr->color = get_texture_spr(spr, mlx, x, y);
			if (spr->color != 0)
			{
				put_pixel(mlx->img, (x + spr->sx), (y + spr->sy), spr->color);
			}
			y++;
		}
		x++;
	}
}

double		size_spr(t_raycast *ray, t_map *map)
{
	double dist_A;
	double dist_B;

	dist_A = (ray->tmp_x - ray->A.x) * (ray->tmp_x - ray->A.x);
	dist_A = dist_A + (ray->tmp_y - ray->A.y) * (ray->tmp_y - ray->A.y);
	dist_A = sqrt(dist_A);
	dist_B = (ray->tmp_x - ray->B.x) * (ray->tmp_x - ray->B.x);
	dist_B = dist_B + (ray->tmp_y - ray->B.y) * (ray->tmp_y - ray->B.y);
	dist_B = sqrt(dist_B);
	if (dist_A < dist_B)
	{
		ray->dist_spr = dist_A;
	}
	else
	{	
		ray->dist_spr = dist_B;
	}
	return (SIZE_WALL * (map->dist_screen / ray->dist_spr));
}
