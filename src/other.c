/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:33:58 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/19 17:50:04 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		is_id(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (1);
	if (line[0] == 'N' && line[1] == 'O')
		return (2);
	if (line[0] == 'S' && line[1] == 'O')
		return (3);
	if (line[0] == 'W' && line[1] == 'E')
		return (4);
	if (line[0] == 'E' && line[1] == 'A')
		return (5);
	if (line[0] == 'S')
		return (6);
	if (line[0] == 'F' && line[1] == ' ')
		return (7);
	if (line[0] == 'C' && line[1] == ' ')
		return (8);
	else
		return (0);
}

int		is_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == '1' || line[i] == ' ')
		i++;
	if (line[i] == '\0' && (line[i - 2] == '1' || line[i - 2] == ' '))
		return (1);
	return (0);
}

void	vect_mult(t_player *player)
{
	player->v0.x = -1.1 * player->v1.y;
	player->v0.y = 1.1 * player->v1.x;
}

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			put_pixel(mlx->img, (x + i), (y + j), color);
			j++;
		}
		i++;
	}
}

int		check_map(t_map *map)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (is_good_char(map->map[i][j]) == 0)
				return (0);
			if (map->map[i][j] == 'W' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'N' || map->map[i][j] == 'S')
				count++;
			if (!(check_map2(map, i, j)))
				return (0);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}
