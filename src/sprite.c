/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:16:40 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/13 22:58:29 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void		draw_sprite(t_mlx *mlx, t_raycast *ray)
{
	int		i;

	i = ray->nb_sprite - 1;
	while (i >= 0)
	{
		printf("dist:%f\nsize:%f\nmapx:%d\nmapy:%d\nsx:%d\nsy:%d\nstart:%d\nxmax:%d\n------------------\n", ray->spr[i]->dist, ray->spr[i]->size, ray->spr[i]->mapx, ray->spr[i]->mapy, ray->spr[i]->sx, ray->spr[i]->sy, ray->spr[i]->start, ray->spr[i]->xmax);
		display_sprite(mlx, ray->spr[i], ray);
		i--;
	}
	printf("\n------------------------\n");
}

void		init_sprite(t_raycast *ray)
{
	int		i;

	i = 0;
	ray->nb_sprite = 0;
	ray->dist_spr = 0;
	ray->start = 0;
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

		ray->start = 0;
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
		ray->spr[i]->mapx = x;
		ray->spr[i]->mapy = y;
		ray->spr[i]->size = size_spr(ray, map, ray->spr[i]);
		ray->spr[i]->dist = ray->dist_spr;
		ray->spr[i]->start = ray->start * (map->dist_screen / ray->spr[i]->dist);
		ray->spr[i]->xmax = 1;
		ray->nb_sprite++;
	}
	else if (ray->spr[i - 1]->mapx == x || ray->spr[i - 1]->mapy == y)
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

	x = spr->start;
	spr->sx -= spr->start;
	if ((y + spr->sy) < 0)
		y++;
	if ((x + spr->sx) < 0)
		x++;
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

double		size_spr(t_raycast *ray, t_map *map, t_sprite *spr)
{
	double dist;
	t_point	A;
	double dist_B;
	double dist_A;

	A.x = (spr->mapx + 0.5) * SIZE_WALL;
	A.y = (spr->mapy + 0.5) * SIZE_WALL;
	dist_A = (ray->tmp_x - ray->A.x) * (ray->tmp_x - ray->A.x);
	dist_A = dist_A + (ray->tmp_y - ray->A.y) * (ray->tmp_y - ray->A.y);
	dist_A = sqrt(dist_A);
	dist_B = (ray->tmp_x - ray->B.x) * (ray->tmp_x - ray->B.x);
	dist_B = dist_B + (ray->tmp_y - ray->B.y) * (ray->tmp_y - ray->B.y);
	dist_B = sqrt(dist_B);
	
	dist = (ray->tmp_x - A.x) * (ray->tmp_x - A.x);
	dist = dist + (ray->tmp_y - A.y) * (ray->tmp_y - A.y);
	dist = sqrt(dist);

	printf("A.x: %f\nA.y: %f\nB.x: %f\nB.y: %f\ndist_A: %f\ndist_B: %f\n____________\n", ray->A.x, ray->A.y, ray->B.x, ray->B.y, dist_A, dist_B);
	if (dist_A <= dist_B)
	{
		if (ray->angle.y <= 0)
		{
			write(1, "A\n", 2);
			ray->start = (int)ray->A.x % SIZE_WALL;
		}
		else
		{
			write(1, "B\n", 2);
			ray->start = SIZE_WALL - ((int)ray->A.x % SIZE_WALL);
		}
//		ray->dist_spr = dist_A;
	}
	else 
	{
		if (ray->angle.x >= 0)
		{
			write(1, "C\n", 2);
			ray->start = (int)ray->B.y % SIZE_WALL;
		}
		else
		{
			write(1, "D\n", 2);
			ray->start = SIZE_WALL - ((int)ray->B.y % SIZE_WALL);
		}
//		ray->dist_spr = dist_B;
	}
	ray->dist_spr = dist;
	return (SIZE_WALL * (map->dist_screen / ray->dist_spr));
}
/*
double		size_spr(t_raycast *ray, t_map *map, t_sprite *spr)
{
	double dist;
	t_point	A;

	A.x = (spr->mapx + 0.5) * SIZE_WALL;
	A.y = (spr->mapy + 0.5) * SIZE_WALL;

	dist = (ray->tmp_x - A.x) * (ray->tmp_x - A.x);
	dist = dist + (ray->tmp_y - A.y) * (ray->tmp_y - A.y);
	dist = sqrt(dist);

	if (ray->angle.y < -(sqrt(2)/2))
//		&& ray->angle.x > -(sqrt(2)/2)
//		&& ray->angle.x < (sqrt(2)/2))
	{
		write(1, "A\n", 2);
		ray->start = (int)ray->A.x % SIZE_WALL;
	}
	else if (ray->angle.y > (sqrt(2)/2))
//		&& ray->angle.x > -(sqrt(2)/2)
//		 && ray->angle.x < (sqrt(2)/2))
	{
		write(1, "B\n", 2);
		ray->start = SIZE_WALL - ((int)ray->A.x % SIZE_WALL);
	}
	else if (ray->angle.x < -(sqrt(2)/2))
//		&& ray->angle.y > -(sqrt(2)/2)
//		&& ray->angle.y < (sqrt(2)/2))
	{
		write(1, "C\n", 2);
		ray->start = (int)ray->B.y % SIZE_WALL;
	}
	else if (ray->angle.x > (sqrt(2)/2))
//		&& ray->angle.y > -(sqrt(2)/2)
//		&& ray->angle.y < (sqrt(2)/2))
	{
		write(1, "D\n", 2);
		ray->start = SIZE_WALL - ((int)ray->B.y % SIZE_WALL);
	}
	ray->dist_spr = dist;
	return (SIZE_WALL * (map->dist_screen / ray->dist_spr));
}
*/
