/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:37:57 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/07 22:11:58 by ylegzoul         ###   ########.fr       */
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
	while (x < mlx->res_x)
	{
		get_ray_angle(x, player, map, ray);
		raycast(map, player, &ray);
		draw_column(mlx, ray, x);
		x++;
		if (x < mlx->res_x / 2)
			ray->total_angle =  -(x - mlx->res_x / 2) * tmp;
		else
			ray->total_angle = (x - mlx->res_x / 2) * tmp;

	}
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
//		get_texture(ray, mlx, x, y);
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
//		get_texture(ray, mlx, x, y);
		put_pixel(mlx->img, x, y, ray->floor);
		y++;
	}
}
/*
void		draw_map(t_mlx *mlx, t_player *player, t_map *map)
{
	int		x;
int		y;

}*/
