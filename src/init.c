/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:38:01 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/16 19:49:45 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		init_mlx(t_mlx *mlx, t_parse *data)
{
	mlx->res_x = data->res_x;
	mlx->res_y = data->res_y;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, mlx->res_x, mlx->res_y, "cub3D");
	mlx->img = new_image(mlx, mlx->res_x, mlx->res_y);
}

void		init_data(t_map **map, t_player **player, t_mlx **mlx, t_hook **hook)
{
	(*mlx) = malloc(sizeof(t_mlx));
    (*map) = malloc(sizeof(t_map));
	(*map)->map = NULL;
	(*map)->size_x = 0;
	(*map)->size_y = 0;
	(*map)->dist_screen = 0;
    (*player) = malloc(sizeof(t_player));
	(*player)->pos.x = 0;
	(*player)->pos.y = 0;
	(*player)->v0.x = 0;
	(*player)->v0.y = 0;
	(*player)->v1.x = 0;
	(*player)->v1.y = 0;
	(*hook) = malloc(sizeof(t_hook));
	(*hook)->mlx = (*mlx);
	(*hook)->map = (*map);
	(*hook)->player = (*player);
}

void		init_data2(t_parse **data, t_raycast **ray, t_hook **hook)
{
	(*data) = malloc(sizeof(t_parse));
	(*data)->res_x = 0;
	(*data)->res_y = 0;
	(*data)->tex_no = NULL;
	(*data)->tex_su = NULL;
	(*data)->tex_we = NULL;
	(*data)->tex_ea = NULL;
	(*data)->tex_spr = NULL;
	(*data)->sol.r = 0;
	(*data)->sol.g = 0;
	(*data)->sol.b = 0;
	(*data)->plafond.r = 0;
	(*data)->plafond.g = 0;
	(*data)->plafond.b = 0;
	(*ray) = malloc(sizeof(t_raycast));
	(*ray)->Xa = 0;
	(*ray)->Ya = 0;
	(*ray)->A.x = 0;
	(*ray)->A.y = 0;
	(*ray)->B.x = 0;
	(*ray)->B.y = 0;
	(*ray)->tmp_x = 0;
	(*ray)->tmp_y = 0;
	(*ray)->dist_wall = 0;
	(*ray)->wall = 0;
	(*hook)->ray = (*ray);
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

	printf("____________________ MAP _________________________\n");

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
*/	printf("__________________ PLAYER ______________________\n");

	printf("\n");
	printf("position x: %f\n", player->pos.x);
	printf("position y: %f\n", player->pos.y);
	printf("\n");
	printf("vecteur x: %f\n", player->v1.x);
	printf("vecteur y: %f\n", player->v1.y);
	printf("\n");
	printf("\n");

	printf("__________________ RAYCAST ______________________\n");


	printf("RAYx: %f\n", ray->angle.x);
	printf("RAYy: %f\n", ray->angle.y);
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
