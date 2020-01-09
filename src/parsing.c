/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:39:04 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/06 19:28:38 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int			parse_file(char **av, t_parse **data, t_map **map, t_player **player)
{
	t_list	*li;
	t_list	*tmp;
	int		fd;
//	int		ret;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	li = NULL;
	while (/*ret == */get_next_line(fd, &line))
	{
	//	if (ret == -1)
	//		return (0);
		tmp = ft_lstnew(line);
		ft_lstadd_back(&li, tmp);
	}
	tmp = li;
	while (li->next)
	{
		if (is_id(li->content) == 1)
			parse_res(li, data, *map);
		if (is_id(li->content) >= 2 && is_id(li->content) <= 6)
			parse_tex(li, data);
		if (is_id(li->content) == 7 || is_id(li->content) == 8)
			parse_color(li, data);
		if (is_map_line(li->content) == 1)
		{
			get_size_map(li, map);
			parse_map(li, map);
		}
		li = li->next;
	}
	parse_player(*map, player);
	li = tmp;
	ft_lstclear(&li, &free);
	return (1);
}

void		parse_res(t_list *li, t_parse **data, t_map *map)
{
	char	**split;

	split = ft_split(li->content, ' ');
	(*data)->res_x = ft_atoi(split[1]);
	(*data)->res_y = ft_atoi(split[2]);
	if ((*data)->res_x > LARGEUR_SCREEN)
		(*data)->res_x = LARGEUR_SCREEN;
	if ((*data)->res_y > HAUTEUR_SCREEN)
		(*data)->res_y = HAUTEUR_SCREEN;
	map->res_x = (*data)->res_x;
	map->res_y = (*data)->res_y;
	ft_free_split(split);
}

void		parse_tex(t_list *li, t_parse **data)
{
	char	**split;

	split = ft_split(li->content, ' ');
	if (is_id(split[0]) == 2)
	{
		(*data)->tex_no = malloc(sizeof(char) * (ft_strlen(split[1]) + 1));
		ft_strcpy((*data)->tex_no, split[1]);
	}
	if (is_id(split[0]) == 3)
	{	
		(*data)->tex_su = malloc(sizeof(char) * (ft_strlen(split[1]) + 1));
		ft_strcpy((*data)->tex_su, split[1]);
	}
	if (is_id(split[0]) == 4)
	{
		(*data)->tex_we = malloc(sizeof(char) * (ft_strlen(split[1]) + 1));
		ft_strcpy((*data)->tex_we, split[1]);
	}
	if (is_id(split[0]) == 5)
	{
		(*data)->tex_ea = malloc(sizeof(char) * (ft_strlen(split[1]) + 1));
		ft_strcpy((*data)->tex_ea, split[1]);
	}
	if (is_id(split[0]) == 6)
	{
		(*data)->tex_spr = malloc(sizeof(char) * (ft_strlen(split[1]) + 1));
		ft_strcpy((*data)->tex_spr, split[1]);
	}
	ft_free_split(split);
}

void		parse_color(t_list *li, t_parse **data)
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

void		parse_map(t_list *li, t_map **map )
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

void		parse_player(t_map *map, t_player **player)
{
	int		i;
	int		j;
	char	tmp;
	double	tmp_angle;

	j = 0;
	tmp_angle = (LARGEUR_CHAMP / 2 * M_PI) / 180;
	map->dist_screen = (LARGEUR_SCREEN/2) / tan(tmp_angle); 
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

	i = 1 ;
	j = 1;
	while (((char *)(li->content))[i] != '\0')
	{
		i++;
	}
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
