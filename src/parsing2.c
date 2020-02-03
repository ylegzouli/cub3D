/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:39:39 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/19 19:06:26 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		parse_color(t_list *li, t_parse **data)
{
	char	**split;

	split = ft_split(&((li->content)[2]), ',');
	if (is_id(li->content) == 7)
	{
		(*data)->sol.r = abs(ft_atoi(split[0]));
		(*data)->sol.g = abs(ft_atoi(split[1]));
		(*data)->sol.b = abs(ft_atoi(split[2]));
	}
	if (is_id(li->content) == 8)
	{
		(*data)->plafond.r = abs(ft_atoi(split[0]));
		(*data)->plafond.g = abs(ft_atoi(split[1]));
		(*data)->plafond.b = abs(ft_atoi(split[2]));
	}
	if ((*data)->sol.r > 255 || (*data)->sol.g > 255 || (*data)->sol.b > 255
		|| (*data)->plafond.r > 255 || (*data)->plafond.g > 255
		|| (*data)->plafond.b > 255)
	{
		ft_free_split(split);
		write(1, "Erreur resolution\n", 18);
		return (0);
	}
	ft_free_split(split);
	return (1);
}

int		parse_map(t_list *li, t_map **map)
{
	int		i;
	int		x;
	int		j;

	get_size_map(li, map);
	j = 0;
	while (j < (*map)->size_y)
	{
		i = 0;
		x = 0;
		while (x < (*map)->size_x && is_good_char(((char *)(li->content))[i]))
		{
			if (((char *)(li->content))[i] != ' ')
			{
				((*map)->map)[j][x] = ((char *)(li->content))[i];
				x++;
			}
			i++;
		}
		((*map)->map)[j][x] = '\0';
		li = li->next;
		j++;
	}
	((*map)->map)[j] = NULL;
	return (1);
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
		(*player)->v1.x = 1;
		(*player)->v1.y = 0;
	}
}

void	get_size_map(t_list *li, t_map **map)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 1;
	x = 0;
	while (((char *)(li->content))[i] != '\0')
	{
		i++;
		if (((char *)(li->content))[i] != ' ')
			x++;
	}
	if (i > 0 && is_map_line(li->content))
	{
		while (li->next)
		{
			j++;
			li = li->next;
		}
		(*map)->size_x = x;
		(*map)->size_y = j;
	}
	malloc_map(map);
}
