#include "cub3D.h"

void		init_data(t_parse **data, t_map **map, t_player **player, t_raycast **ray, t_mlx **mlx, t_hook **hook)
{
	(*data) = malloc(sizeof(t_parse));
    (*map) = malloc(sizeof(t_map));
    (*player) = malloc(sizeof(t_player));
    (*ray) = malloc(sizeof(t_raycast));
 	
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

	(*map)->map = NULL;
	(*map)->size_x = 0;
	(*map)->size_y = 0;
	(*map)->dist_screen = 0;

	(*player)->pos.x = 0;
	(*player)->pos.y = 0;
	(*player)->v0.x = 0;
	(*player)->v0.y = 0;
	(*player)->v1.x = 0;
	(*player)->v1.y = 0;

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

	(*hook)->mlx = (*mlx);
	(*hook)->ray = (*ray);
	(*hook)->map = (*map);
	(*hook)->player = (*player);
}
