/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:37:57 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/13 22:58:31 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void		affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player )
{
	int		x;
	double	tmp;

	x = 0;
	tmp = (double)LARGEUR_CHAMP / (double)mlx->res_x;
	vect_mult(player);
	clear_image(mlx->img, mlx->res_x, mlx->res_y);	
	init_sprite(ray);
	while (x < mlx->res_x)
	{
		get_ray_angle(x, player, map, ray);
		raycast(map, player, &ray);
	//	save_pos_spr(ray, x, map);
		draw_column(mlx, ray, x);
		x++;
		if (x < mlx->res_x / 2)
			ray->total_angle =  -(x - mlx->res_x / 2) * tmp;
		else
			ray->total_angle = (x - mlx->res_x / 2) * tmp;
	}
	calc_dist_sprite(ray->spr, player, map);
	if (player->cible == 1)
		draw_cible(mlx);
	if (player->arme == 1)
		draw_arme(mlx);
	if (player->map == 1)
		draw_map(mlx, player, map);
	draw_sprite(ray->spr, mlx, player, map);
	clear_sprite(ray->spr);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}

void		draw_column(t_mlx *mlx, t_raycast *ray, int x)
{
	int		y;
	int		start;
	int		end;

	start = (mlx->res_y - ray->wall) / 2;
	end = start + ray->wall;
	if (start < 0)
		start = 0;
	if (end > mlx->res_y - 1)
		end = mlx->res_y - 1;
	y = 0;
	while (y < start)
	{
		put_pixel(mlx->img, x, y, ray->ceil);
		y++;
	}
	while (y < end)
	{
		get_texture(ray, mlx, x, y);
		put_pixel(mlx->img, x, y, ray->color);
		y++;
	}
	while (y < mlx->res_y)
	{
		put_pixel(mlx->img, x, y, ray->floor);
		y++;
	}
}

void		draw_arme(t_mlx *mlx)
{
	int		x;
	int		y;
	int		tmpx;
	int		tmpy;
	int		color;

	x = LARGEUR_SCREEN - mlx->arme->l;
	tmpx = 0;
	while (tmpx < mlx->arme->l)
	{
		y = HAUTEUR_SCREEN - 350;
		tmpy = 0;
		while (tmpy < 350)
		{
			color =	get_pixel(mlx->arme, tmpx, tmpy);
			if (color != 16185078 && color < 13181000 && color)
				put_pixel(mlx->img, x, y, color);
			y++;
			tmpy++;
		}
		x++;
		tmpx++;
	}
}

void		draw_cible(t_mlx *mlx)
{
	int		x;
	int		y;
	int		tmpx;
	int		tmpy;
	int		color;

	x = LARGEUR_SCREEN / 2 - 30;
	tmpx = 0;
	while (tmpx < mlx->arme->l)
	{
		y = HAUTEUR_SCREEN / 2 - 30;
		tmpy = 0;
		while (tmpy < 350)
		{
			color = get_pixel(mlx->cible, tmpx, tmpy);
			if (color != 0 && color != 16777215 && color < 14314043)
				put_pixel(mlx->img, x, y, 1611000);
			y++;
			tmpy++;
		}
		x++;
		tmpx++;
	}
}


void		draw_map(t_mlx *mlx, t_player *player, t_map *map)
{
	int		x;
	int		y;

	x = 0;
	while (x < map->size_x + 1)
	{
		draw_square(mlx, (x * 5), 0, 0);
		x++;
	}
	y = 0;
	while (y < map->size_y + 1)
	{
		draw_square(mlx, 0, (y * 5), 0);
		y++;
	}
	x = 0;
	while (x < map->size_x)
	{
		y = 0;
		while (y < map->size_y)
		{
			if (map->map[y][x] == '1')
				draw_square(mlx, (x * 5 + 5), (y * 5 + 5), 13158600);
			else
				draw_square(mlx, (x * 5 + 5), (y * 5 + 5), 200);
			if (x == (int)player->pos.x && y == (int)player->pos.y)
				draw_square(mlx, (x * 5 + 5), (y * 5 + 5), 16711680);
			y++;
		}
		x++;
	}
}

