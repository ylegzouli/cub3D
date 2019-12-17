/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:37:57 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/16 19:49:00 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player )
{
	int		x;
	double	angle;
	double	tmp;

	x = 0;
	tmp = (double)LARGEUR_CHAMP / (double)LARGEUR_SCREEN;
	vect_mult(player);
	clear_image(mlx->img, LARGEUR_SCREEN, HAUTEUR_SCREEN);	
	while (x < LARGEUR_SCREEN)
	{
		get_ray_angle(x, player, map, ray);
		raycast(map, player, &ray);
		get_texture(ray);
		draw_column(mlx, ray, x);
		x++;
		if (x < LARGEUR_SCREEN / 2)
			ray->total_angle =  -(x - LARGEUR_SCREEN / 2) * tmp;
		else
			ray->total_angle = (x - LARGEUR_SCREEN / 2) * tmp;

	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}

void		draw_column(t_mlx *mlx, t_raycast *ray, int x)
{
	int		y;
	int		start;
	int		end;

	start = (HAUTEUR_SCREEN - ray->wall) / 2;
	end = start + ray->wall;
	if (start < 0)
		start = 0;
	if (end > HAUTEUR_SCREEN - 1)
		end = HAUTEUR_SCREEN - 1;
	y = start; 
	while (y < end)
	{
		put_pixel(mlx->img, x, y, ray);
		y++;
	}
}

void		get_texture(t_raycast *ray)
{
	if (ray->tex == 'N' || ray->tex == 'S')
		ray->color = 16711680;
	else
		ray->color = 14417920;
}

