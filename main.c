#include "cub3D.h"

int		main(int ac, char **av)
{
	t_parse		*data;
	t_map		*map;
	t_player	*player;
	t_raycast	*ray;

	init_data(&data, &map, &player, &ray);
	parse_file(av, &data, &map, &player);
	raycast(map, player, &ray);
	write(1, "ICI\n", 4);	

	ft_print_debugage(data, map, player, ray);
	return (1);
}
