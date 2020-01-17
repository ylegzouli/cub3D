/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:38:26 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:38:56 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		check_map2(t_map *map, int i, int j)
{
	if (map->map[i][j] != '0' && map->map[i][j] != '1'
		&& map->map[i][j] != '2' && map->map[i][j] != 'W'
		&& map->map[i][j] != 'E' && map->map[i][j] != 'N'
		&& map->map[i][j] != 'S')
		return (0);
	if ((i == 0 || i == map->size_y - 1 || j == 0
		|| j == map->size_x - 1) && map->map[i][j] != '1')
		return (0);
	return (1);
}

void	ft_free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}
