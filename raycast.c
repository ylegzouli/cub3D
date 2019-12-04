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
/*
void		inter_x(t_map *map, t_player *player)
{
	int			Ax;
	int			Ay;
	int			tmp_angle;
	int			tmp2;
	float		Ya;
	float		Xa;

	player->angle = 89;
	tmp2 = (int)((player->pos.y) / (float)(map->size_y));
	if (tmp_angle < 180)// && tmp_angle > 90)
	{	
		Ya = -1 * (float)(map->size_y);
		Ay = tmp2 * map->size_y - 1;
	}
	else// if (tmp_angle >= 180)
	{	
		Ya = (float)(map->size_y);
		Ay = tmp2 * map->size_y + map->size_y;
	}
	printf("%d\n", Ay);
	Ay = abs(Ay) / map->size_y;
	Ax = (int)((player->pos.x) + ((player->pos.y) / tan(player->angle)));
	Ax = Ax / (map->size_y);
	Ax = abs(Ax);
	Xa = ((float)(map->size_y)) / tan(tmp_angle);
	while ((map->map)[Ay][Ax] != 1)
	{
		Ax = (int)(((float)Ax + Xa) / (float)map->size_y);
		Ay = (int)(((float)Ay + Ya) / (float)map->size_y);
	}
	printf("\nplayer->pos.x :%f\nplayer->pos.y :%f\nplayer->angle :%f\nmap->size_y :%d\nAx :%d\nAy :%d\ntmp_angle :%d\nYa :%f\nXa :%f\ntmp2 :%d\n\n",player->pos.x, player->pos.y, player->angle, map->size_y, Ax, Ay, tmp_angle, Ya, Xa, tmp2);
}
*/
void        inter_x(t_map *map, t_player *player)
{
    int         Ax;
    int         Ay;
    int         tmp_angle;
    float       tmp2;
    float       Ya;
    float       Xa;
	int			size_y;

	player->angle = 89;
	tmp_angle = (int)(player->angle) - ((int)(player->angle) / 360) * 360;
	tmp2 = (player->pos.y) / (float)(map->size_y);
	tmp2 = (int)tmp2;
	if (tmp_angle < 180)
	{
		Ay = tmp2 * size_y - 1;
	}
	else// if (tmp_angle >= 180)
	{
		Ay = tmp2 * size_y + size_y;
	}

	
	printf("tmp_angle = %d\n", tmp_angle);
	printf("tmp2 = %f\n", tmp2);
	printf("Ay = %d\n", Ay);

}


/*
t_point		inter_y(t_map *map, t_player *player)
{
	t_point     B;
    int         tmp;
    int         tmp2

    B = malloc(sizeof(t_point));
    tmp = player->angle - (player->angle / 360) * 360;
    tmp2 = player->pos.y / map->size_y;
    if (tmp < 180)
        A->y = (tmp2 * map->size - 1) / map->size_y;
    else if (tmp >= 180)
        A->y = (tmp2 * map->size + map->size_y) / map->size_y;
    A->x = player->pos.x + ((player->pos.y)/tan(player->angle));
    A->x = A->x / map->size_y;
    return (A);
}

int			distance_mur()
{
}

int			taille_mur()
{
}*/
