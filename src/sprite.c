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

void		dist_spr(t_raycast *ray, t_map *map)
{
	double dist_A;
	double dist_B;

	dist_A = (ray->tmp_x - ray->sprA.x) * (ray->tmp_x - ray->sprA.x);
	dist_A = dist_A + (ray->tmp_y - ray->sprA.y) * (ray->tmp_y - ray->sprA.y);
	dist_A = sqrt(dist_A);
	dist_B = (ray->tmp_x - ray->sprB.x) * (ray->tmp_x - ray->sprB.x);
	dist_B = dist_B + (ray->tmp_y - ray->sprB.y) * (ray->tmp_y - ray->sprB.y);
	dist_B = sqrt(dist_B);
	if (dist_A < dist_B)
		ray->dist_spr = dist_A;
	else
		ray->dist_spr = dist_B;
	if (!ray->sprite)
		ray->sprite = SIZE_WALL * (map->dist_screen / ray->dist_spr);
}

void		draw_spr_column(t_raycast *ray, t_map *map, t_mlx *mlx, int x)
{
	int		y;
	int		start;

	dist_spr(ray, map);
	start = 0;
	y = start;
	while (y < ray->sprite)
	{
		get_texture_spr(ray, mlx, x, y);
		if (ray->spr_color != 0)
			put_pixel(mlx->img, x, y, ray->spr_color);
		y++;
	}

}
