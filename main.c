#include "cub3D.h"

int		main(int ac, char **av)
{
	t_parse		*data;
	t_map		*map;

	data = malloc(sizeof(t_parse));
	map = malloc(sizeof(t_map));

	parse_file(av, &data, &map);
	return (1);
}
