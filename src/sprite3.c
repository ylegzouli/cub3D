/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:44:15 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/17 15:44:39 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		draw_sprite(t_sprite *spr, t_mlx *mlx, t_player *player, t_map *map)
{
	while (spr)
	{
		calc_data_spr(spr, player, map);
		if (spr->x != 0.5 && spr->y != 0.5)
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
		if (mlx->tab[x] > spr->dist * SIZE_WALL)
		{
			while (y < spr->end_y)
			{
				color = get_texture_spr(spr, mlx,
				(x - spr->start_x + spr->cutx), (y - spr->start_y + spr->cuty));
				if (color != 0)
					put_pixel(mlx->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}
