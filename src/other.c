/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:33:58 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/04 14:39:05 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
	while (line[i] == '1')
		i++;
	if (line[i] == '\0' && line[i - 2] == '1')
		return (1);
	return (0);
}

void	vect_mult(t_player *player)
{
	player->v0.x = -player->v1.y;
	player->v0.y = player->v1.x;
}
/*
void	draw_pos(t_mlx *mlx, t_map *map, t_player *player)
{
	
}
*/
void		ft_free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
}
