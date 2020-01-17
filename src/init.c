/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:38:01 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:16:52 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		init_mlx(t_mlx *mlx, t_parse *data)
{
	mlx->res_x = data->res_x;
	mlx->res_y = data->res_y;
	if (!(mlx->ptr = mlx_init()))
		return (0);
	if (!(mlx->win = mlx_new_window(mlx->ptr, mlx->res_x, mlx->res_y, "cub3D")))
		return (0);
	if (!(mlx->img = new_image(mlx, mlx->res_x, mlx->res_y)))
		return (0);
	return (1);
}

int		init_data(t_map **map, t_player **player, t_mlx **mlx, t_hook **hook)
{
	if (!((*mlx) = malloc(sizeof(t_mlx))))
		return (0);
	if (!((*map) = malloc(sizeof(t_map))))
		return (0);
	(*map)->map = NULL;
	(*map)->size_x = 0;
	(*map)->size_y = 0;
	(*map)->dist_screen = 0;
	if (!((*player) = malloc(sizeof(t_player))))
		return (0);
	(*player)->pos.x = 0;
	(*player)->pos.y = 0;
	(*player)->v0.x = 0;
	(*player)->v0.y = 0;
	(*player)->v1.x = 0;
	(*player)->v1.y = 0;
	(*player)->arme = 0;
	(*player)->cible = 0;
	(*player)->map = 0;
	if (!((*hook) = malloc(sizeof(t_hook))))
		return (0);
	(*hook)->mlx = (*mlx);
	(*hook)->map = (*map);
	(*hook)->player = (*player);
	return (1);
}

int		init_data2(t_parse **data, t_raycast **ray, t_hook **hook)
{
	if (!((*data) = malloc(sizeof(t_parse))))
		return (0);
	(*data)->tex_no = NULL;
	(*data)->tex_su = NULL;
	(*data)->tex_we = NULL;
	(*data)->tex_ea = NULL;
	(*data)->tex_spr = NULL;
	(*data)->plafond.r = 0;
	(*data)->plafond.g = 0;
	(*data)->plafond.b = 0;
	if (!((*ray) = malloc(sizeof(t_raycast))))
		return (0);
	(*ray)->xa = 0;
	(*ray)->xa = 0;
	(*ray)->a.x = 0;
	(*ray)->a.y = 0;
	(*ray)->b.x = 0;
	(*ray)->b.y = 0;
	(*ray)->tmp_x = 0;
	(*ray)->tmp_y = 0;
	(*ray)->dist_wall = 0;
	(*ray)->wall = 0;
	(*hook)->ray = (*ray);
	(*hook)->data = (*data);
	return (1);
}
