/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:38:26 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/17 18:04:32 by ylegzoul         ###   ########.fr       */
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

int		is_good_char(char c)
{
	if (c != '1' && c != '0' && c != '2' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W')
		return (0);
	return (1);
}

int		check_size_map(char **m, t_map *map)
{
	int		i;

	i = 0;
	while (m[i])
	{
		if (ft_strlen(m[i]) != map->size_x)
			return (0);
		i++;
	}
	return (1);
}

int		malloc_map(t_map **map)
{
	int j;

	j = 0;
	if (!((*map)->map = malloc(sizeof(char *) * ((*map)->size_y + 1))))
		return (0);
	while (j < (*map)->size_y)
	{
		if (!(((*map)->map)[j] = malloc(sizeof(char) * ((*map)->size_x + 1))))
			return (0);
		j++;
	}
	return (1);
}
