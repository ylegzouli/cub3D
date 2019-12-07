#include "cub3D.h"

int		main(int ac, char **av)
{
	t_parse		*data;
	t_map		*map;
	t_player	*player;
	t_raycast	*ray;
	t_mlx		*mlx;
	t_hook		*hook;

//---------> a mettre dans init
	mlx = malloc(sizeof(t_mlx));
	hook = malloc(sizeof(t_hook));	
	
	init_data(&data, &map, &player, &ray, &mlx, &hook);
	parse_file(av, &data, &map, &player);
	init_mlx(mlx);
	affichage(mlx, ray, map, player);
	mlx_hook(mlx->win, 2, 1L << 0, hook_keydown, hook);

//	ft_print_debugage(data, map, player, ray);
	mlx_loop(mlx->ptr);
	return (1);
}
