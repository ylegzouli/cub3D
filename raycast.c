/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:35:53 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/04 16:02:31 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		raycast(t_map *map, t_player *player, t_raycast **ray)
{
	inter_x(map, player, ray);
}

void        inter_x(t_map *map, t_player *player, t_raycast **ray)
{
	int		tmp;
	float	tmp_angle;
	float	tmp_x;
	float	tmp_y;

	player->angle = 315;
	tmp_y = player->pos.y * 64;
	tmp_x = player->pos.x * 64;
	tmp_angle = (int)(player->angle) - ((int)(player->angle) / 360) * 360;
	tmp = (int)(tmp_y / 64);
	if (tmp_angle < 180)
    {
        (*ray)->Ya = -64;
        (*ray)->A.y = tmp * 64 - 1;
    }
    else
    {
        (*ray)->Ya = 64;
        (*ray)->A.y = tmp * 64 + 64;
    }
	tmp_angle = (tmp_angle * 3.14) / 180;
	(*ray)->A.x = tmp_x + (tmp_y - (*ray)->A.y) / tan(tmp_angle);
	(*ray)->Xa = 64 / tan(tmp_angle);
	inter_x2(map, ray);
}

void		inter_x2(t_map *map, t_raycast **ray)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = (*ray)->A.x / 64;
	tmp_y = (*ray)->A.y / 64;
	while (tmp_y < map->size_y && tmp_x < map->size_x && (map->map)[tmp_y][tmp_x] != '1')
	{
		(*ray)->A.x = (*ray)->A.x + (*ray)->Xa;
		(*ray)->A.y = (*ray)->A.y + (*ray)->Ya;
		tmp_x = (*ray)->A.x / 64;
		tmp_y = (*ray)->A.y / 64;
//		printf("tmp_x: %d\ntmp_y: %d\nA.x: %f\nA.y: %f\n___________________________________________\n", tmp_x, tmp_y, (*ray)->A.x, (*ray)->A.y);
	}
	(*ray)->A.x = tmp_x;
	(*ray)->A.y = tmp_y;
}

/*
t_point		inter_y(t_map *map, t_player *player)
{
}
*/

int			distance_mur()
{

}

/*
int			taille_mur()
{
}
*/
