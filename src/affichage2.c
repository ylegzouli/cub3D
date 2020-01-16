/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:33:02 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:33:59 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		draw_map(t_mlx *mlx, t_player *player, t_map *map)
{
	int		x;
	int		y;

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
