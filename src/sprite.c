/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:16:40 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/09 19:55:03 by ylegzoul         ###   ########.fr       */
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
		ray->spr[i]->xmax = 0;
		ray->spr[i]->imgx = 0;
		ray->spr[i]->imgy = 0;
		ray->spr[i]->color = 0;
		ray->spr[i]->start = 0;
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
		ray->spr[i]->start = ray->start;;
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
		ray->spr[i - 1]->sy = (HAUTEUR_SCREEN / 2) - 32 * (map->dist_screen / ray->dist_spr);// HAUTEUR_SCREEN / 2;  /// SIZE_WALL, ray->spr[i]->dist, ray->spr[i]->size, HAUTEUR_SCREEN ///
	}
	else if (i == 0 && ray->spr[i]->mapx != 0)
	{
		ray->spr[i]->sx = x;
		ray->spr[i - 1]->sy = (HAUTEUR_SCREEN / 2) - 32 * (map->dist_screen / ray->dist_spr);// HAUTEUR_SCREEN / 2;  /// SIZE_WALL, ray->spr[i]->dist, ray->spr[i]->size, HAUTEUR_SCREEN ///
	}
}

void		display_sprite(t_mlx *mlx, t_sprite *spr, t_raycast *ray)
{
	int		x;
	int		y;

	x = spr->start;
	if (spr->sx < 0)
	{
		spr->xmax -= spr->sx;
		spr->sx = 0;
	}
	while ((spr->sx + x) < (spr->sx + spr->xmax))
	{
		y = 0;
		while ((spr->sy + y) < (spr->sy + spr->size))
		{
			spr->color = get_texture_spr(spr, mlx, x, y);
			if (spr->color != 0 
				&& (get_pixel(mlx->img, (spr->sx + x), (spr->sy + y) != ray->color)
				|| !(get_pixel(mlx->img, (spr->sx + x), (spr->sy + y)))))
				put_pixel(mlx->img, (x + spr->sx), (y + spr->sy), spr->color);
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
		ray->start = (int)(ray->A.x) % SIZE_WALL;
		ray->dist_spr = dist_A;
	}
	else
	{	
		ray->start = (int)(ray->B.x) % SIZE_WALL;
		ray->dist_spr = dist_B;
	}
	return (SIZE_WALL * (map->dist_screen / ray->dist_spr));
}
