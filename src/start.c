#include "../include/cub3D.h"

int		main(int ac, char **av)
{
	t_parse		*data;
	t_mlx		*mlx;

	if (!(start(mlx, data, ac, av)))
	{
		free(data);
		free(mlx);
		write(1, "Error\n", 6);
		return (0);
	}
	return (1);
}

int		start(t_mlx *mlx, t_parse *data, int ac, char **av)
{
	t_map		*map;
	t_player	*player;
	t_hook		*hook;
	t_raycast	*ray;

	if (!(init_data(&map, &player, &mlx, &hook)))
		return (0);
	if (!(init_data2(&data, &ray, &hook)))
		return (0);
	if (!(parse_file(av, &data, &map, &player)))
		return (0);
	if (!(check_map(map)))
		return (0);
	get_texture_fnc(ray, data);
	if (!(init_mlx(mlx, data)))
		return (0);
	if (!(init_texture(data, mlx)))
		return (0);
	affichage(mlx, ray, map, player);
	opt_save_bmp(mlx, ac, av);
	mlx_hook(mlx->win, 2, 1L << 0, hook_keydown, hook);
	mlx_loop(mlx->ptr);
	return (1);
}

