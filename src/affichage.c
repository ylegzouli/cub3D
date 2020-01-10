/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:37:57 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/09 20:15:55 by ylegzoul         ###   ########.fr       */
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
		save_pos_spr(ray, x, map);
		draw_column(mlx, ray, x);
		x++;
		if (x < mlx->res_x / 2)
			ray->total_angle =  -(x - mlx->res_x / 2) * tmp;
		else
			ray->total_angle = (x - mlx->res_x / 2) * tmp;

	}
//	draw_arme(mlx);
	draw_sprite(mlx, ray);
//	printf("nb_sprite=%d \ndist_sprite=%f \ndist=%f \nsize=%f \nmapx=%d\nmapy=%d\nimgx=%d\nimgy=%d\nsx=%d\nsy=%d\nxmax=%d\ncolor=%d\n______________________________\n", ray->nb_sprite, ray->dist_spr, ray->spr[0]->dist, ray->spr[0]->size, ray->spr[0]->mapx, ray->spr[0]->mapy, ray->spr[0]->imgx, ray->spr[0]->imgy, ray->spr[0]->sx, ray->spr[0]->sy, ray->spr[0]->xmax, ray->spr[0]->color);
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
/*
void		draw_arme(t_mlx *mlx)
{
	int		x;
	int		y;
	int		tmp;
	int		color;

	x = 0;
	while (x < LARGEUR_SCREEN)
	{
		y = HAUTEUR_SCREEN / 2;
		while (y < HAUTEUR_SCREEN)
		{
			tmp = y * (mlx->arme->l / LARGEUR_SCREEN);
			color =	get_pixel(mlx->arme, (x * (mlx->arme->l / LARGEUR_SCREEN), tmp));
			if (color != )
				put_pixel(mlx, x, y, color);
			y++;
		}
		x++;
}
*/
/*
void		draw_map(t_mlx *mlx, t_player *player, t_map *map)
{
	int		x;
int		y;

}*/
