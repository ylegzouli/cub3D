/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:37:57 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:34:36 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player)
{
	int		x;
	double	tmp;

	x = 0;
	tmp = (double)LARGEUR_CHAMP / (double)mlx->res_x;
	vect_mult(player);
	clear_image(mlx->img, mlx->res_x, mlx->res_y);
	ray->spr = new_sprite(0, 0);
	while (x < mlx->res_x)
	{
		get_ray_angle(x, player, map, ray);
		raycast(map, player, &ray);
		mlx->tab[x] = ray->dist_wall;
		draw_column(mlx, ray, x);
		x++;
		if (x < mlx->res_x / 2)
			ray->total_angle = -(x - mlx->res_x / 2) * tmp;
		else
			ray->total_angle = (x - mlx->res_x / 2) * tmp;
	}
	calc_dist_sprite(ray->spr, player, map);
	draw_sprite(ray->spr, mlx, player, map);
	draw_opt(mlx, player, map);
	clear_sprite(ray->spr);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}

void		draw_opt(t_mlx *mlx, t_player *player, t_map *map)
{
	if (player->cible == 1)
		draw_cible(mlx);
	if (player->arme == 1)
		draw_arme(mlx);
	if (player->map == 1 && map->size_x < map->res_x / 5
		&& map->size_y < map->res_y / 5)
		draw_map(mlx, player, map);
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
	while (y++ < start)
		put_pixel(mlx->img, x, y, ray->ceil);
	while (y < end)
	{
		get_texture(ray, mlx, y);
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

	x = mlx->res_x - mlx->arme->l;
	tmpx = 0;
	while (tmpx < mlx->arme->l)
	{
		y = mlx->res_y - 350;
		tmpy = 0;
		while (tmpy < 350)
		{
			color = get_pixel(mlx->arme, tmpx, tmpy);
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

	x = mlx->res_x / 2 - 30;
	tmpx = 0;
	while (tmpx < mlx->arme->l)
	{
		y = mlx->res_y / 2 - 30;
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
