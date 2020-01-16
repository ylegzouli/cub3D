/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:39:04 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:41:01 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		parse_file(char **av, t_parse **data, t_map **map, t_player **player)
{
	t_list	*li;
	t_list	*tmp;
	int		fd;
	char	*line;
	int		ret;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	li = NULL;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			return (0);
		tmp = ft_lstnew(line);
		ft_lstadd_back(&li, tmp);
	}
	tmp = li;
	if (!(send_line(li, data, map)))
		return (0);
	parse_player(*map, player);
	li = tmp;
	ft_lstclear(&li, &free);
	return (1);
}

int		send_line(t_list *li, t_parse **data, t_map **map)
{
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
	return (1);
}

void	parse_res(t_list *li, t_parse **data, t_map *map)
{
	char	**split;

	split = ft_split(li->content, ' ');
	(*data)->res_x = ft_atoi(split[1]);
	(*data)->res_y = ft_atoi(split[2]);
	if ((*data)->res_x > LARGEUR_SCREEN)
		(*data)->res_x = LARGEUR_SCREEN;
	if ((*data)->res_y > HAUTEUR_SCREEN)
		(*data)->res_y = HAUTEUR_SCREEN;
	if ((*data)->res_x < 400)
		(*data)->res_x = 400;
	if ((*data)->res_y < 400)
		(*data)->res_y = 400;
	map->res_x = (*data)->res_x;
	map->res_y = (*data)->res_y;
	ft_free_split(split);
}

void	parse_tex(t_list *li, t_parse **data)
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
	else
		parse_tex2(split, data);
	ft_free_split(split);
}

void	parse_tex2(char **split, t_parse **data)
{
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
}
