#include "../include/cub3D.h"

int		main(int ac, char **av)
{
	t_parse		*data;
	t_mlx		*mlx;

	start(mlx, data, ac, av);
	return (1);
}

int		start(t_mlx *mlx, t_parse *data, int ac, char **av)
{
	t_map		*map;
	t_player	*player;
	t_hook		*hook;
	t_raycast	*ray;

	init_data(&map, &player, &mlx, &hook);
	init_data2(&data, &ray, &hook);
	parse_file(av, &data, &map, &player);
	get_texture_fnc(ray, data);
	init_mlx(mlx, data);
	init_texture(data, mlx);
	affichage(mlx, ray, map, player);
	opt_save_bmp(mlx, ac, av);
	mlx_hook(mlx->win, 2, 1L << 0, hook_keydown, hook);
	mlx_loop(mlx->ptr);
	return (1);
}

