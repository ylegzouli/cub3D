#include "cub3D.h"

int		main(int ac, char **av)
{
	t_parse		*data;
	t_map		*map;
	t_player	*player;

	data = malloc(sizeof(t_parse));
	map = malloc(sizeof(t_map));
	player = malloc(sizeof(t_player));

	parse_file(av, &data, &map, &player);
	return (1);
}
