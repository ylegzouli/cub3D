/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:39:39 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:40:26 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	parse_color(t_list *li, t_parse **data)
{
	char	**split;

	split = ft_split(&((li->content)[2]), ',');
	if (is_id(li->content) == 7)
	{
		(*data)->sol.r = ft_atoi(split[0]);
		(*data)->sol.g = ft_atoi(split[1]);
		(*data)->sol.b = ft_atoi(split[2]);
	}
	if (is_id(li->content) == 8)
	{
		(*data)->plafond.r = ft_atoi(split[0]);
		(*data)->plafond.g = ft_atoi(split[1]);
		(*data)->plafond.b = ft_atoi(split[2]);
	}
	ft_free_split(split);
}

void	parse_map(t_list *li, t_map **map)
{
	int		i;
	int		j;

	j = 0;
	(*map)->map = malloc(sizeof(char *) * ((*map)->size_y + 1));
	while (j < (*map)->size_y)
	{
		((*map)->map)[j] = malloc(sizeof(char) * ((*map)->size_x + 1));
		j++;
	}
	j = 0;
	while (j < (*map)->size_y)
	{
		i = 0;
		while (i < (*map)->size_x)
		{
			((*map)->map)[j][i] = ((char *)(li->content))[i];
			i++;
		}
		((*map)->map)[j][i] = '\0';
		li = li->next;
		j++;
	}
	((*map)->map)[j] = NULL;
}

void	parse_player(t_map *map, t_player **player)
{
	int		i;
	int		j;
	char	tmp;
	double	tmp_angle;

	j = 0;
	tmp_angle = (LARGEUR_CHAMP / 2 * M_PI) / 180;
	map->dist_screen = (map->res_x / 2) / tan(tmp_angle);
	while (j < map->size_y)
	{
		i = 0;
		while (i < map->size_x)
		{
			if ((map->map)[j][i] == 'N' || (map->map)[j][i] == 'S'
				|| (map->map)[j][i] == 'E' || (map->map)[j][i] == 'W')
			{
				tmp = (map->map)[j][i];
				get_case(player, tmp, i, j);
			}
			i++;
		}
		j++;
	}
}

void	get_case(t_player **player, char tmp, int i, int j)
{
	(*player)->pos.x = i + 0.5;
	(*player)->pos.y = j + 0.5;
	if (tmp == 'N')
	{
		(*player)->v1.x = 0;
		(*player)->v1.y = 1;
	}
	if (tmp == 'S')
	{
		(*player)->v1.x = 0;
		(*player)->v1.y = -1;
	}
	if (tmp == 'E')
	{
		(*player)->v1.x = -1;
		(*player)->v1.y = 0;
	}
	if (tmp == 'W')
	{
		(*player)->v1.x = -1;
		(*player)->v1.y = 0;
	}
}

void	get_size_map(t_list *li, t_map **map)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (((char *)(li->content))[i] != '\0')
		i++;
	if (i > 0 && is_map_line(li->content))
	{
		while (li->next)
		{
			j++;
			li = li->next;
		}
		(*map)->size_x = i;
		(*map)->size_y = j;
	}
}
