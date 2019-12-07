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

#include "cub3D.h"

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

void	get_case(t_player **player, char tmp, int i, int j)
{
	(*player)->pos.x = i + 0.5;
	(*player)->pos.y = j + 0.5;
	if (tmp == 'N')
	{
		(*player)->angle = 90;
		(*player)->vec.x = (*player)->pos.x;
		(*player)->vec.y = (*player)->pos.y - 1;
	}
	if (tmp == 'S')
	{
		(*player)->angle = 270;
		(*player)->vec.x = (*player)->pos.x;
		(*player)->vec.y = (*player)->pos.y + 1;
	}
	if (tmp == 'E')
	{
		(*player)->angle = 0;
		(*player)->vec.x = (*player)->pos.x + 1;
		(*player)->vec.y = (*player)->pos.y;
	}
	if (tmp == 'W')
	{
		(*player)->angle = 180;
		(*player)->vec.x = (*player)->pos.x - 1;
		(*player)->vec.y = (*player)->pos.y;
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

void	ft_print_debugage(/*t_parse *data,*/ t_map *map, t_player *player, t_raycast *ray)
{
	int	i;
/*
	printf("__________________ DATA ______________________\n");
	
	printf("\n");
	printf("couleur rouge sol: %d\n", data->sol.r);
	printf("couleur vert  sol: %d\n", data->sol.g);
	printf("couleur bleu  sol: %d\n", data->sol.b);
	printf("\n");
	printf("couleur rouge plafond: %d\n", data->plafond.r);
	printf("couleur vert  plafond: %d\n", data->plafond.g);
	printf("couleur bleu  plafond: %d\n", data->plafond.b);
	printf("\n");
	printf("resolution x: %d\n", data->res_x);
	printf("resolution y: %d\n", data->res_y);
	printf("\n");
	printf("texture nord: %s\n", data->tex_no);
	printf("texture sud : %s\n", data->tex_su);
	printf("texture west: %s\n", data->tex_we);
	printf("texture east: %s\n", data->tex_ea);
	printf("\n");
	printf("texture sprite: %s\n", data->tex_spr);
	printf("\n");
	
*/	printf("____________________ MAP _________________________\n");

	i = 0;
	printf("\n");
	printf("dist screen: %f\n", map->dist_screen);
	printf("\n");
	printf("size map x: %d\n", map->size_x);
	printf("size map y: %d\n", map->size_y);
	printf("\n");
	while (i < map->size_y)
	{
		printf("%s\n", (map->map)[i]);
		i++;
	}
	printf("\n");
	printf("__________________ PLAYER ______________________\n");
	
	printf("\n");
	printf("position x: %f\n", player->pos.x);
	printf("position y: %f\n", player->pos.y);
	printf("\n");
	printf("vecteur x: %f\n", player->vec.x);
	printf("vecteur y: %f\n", player->vec.y);
	printf("\n");
	printf("angle: %f\n", player->angle);
	printf("\n");

	printf("__________________ RAYCAST ______________________\n");
	
	printf("\n");
	printf("Ya: %f\n", ray->Ya);
	printf("Xa: %f\n", ray->Xa);
	printf("\n");
	printf("A.x: %f\n", ray->A.x);
	printf("A.y: %f\n", ray->A.y);
	printf("\n");
	printf("B.x: %f\n", ray->B.x);
	printf("B.y: %f\n", ray->B.y);
	printf("\n");
	printf("distance mur: %f\n", ray->dist_wall);
	printf("\n");
	printf("taille mur: %f\n", ray->wall);

	printf("_________________________________________________\n");
}
