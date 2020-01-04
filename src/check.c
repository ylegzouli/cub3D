#include "../include/cub3D.h"
/*
int			check_list(t_list *li)
{
	int		i;

	i = 0;

}
*/
int			check_map(t_map *map)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (i < map->res_x)
	{
		j = 0;
		while (j < map->res_y)
		{
			if (map->map[i][j] == 'W' || map->map[i][j] == 'E' 
				|| map->map[i][j] == 'N' || map->map[i][j] == 'S')
				count++;
			if (count <= 1)
			{
				if (map->map[i][j] != '0' || map->map[i][j] != '1' 
					|| map->map[i][j] != 2 || map->map[i][j] != 'W' 
					|| map->map[i][j] != 'E' || map->map[i][j] != 'N' || map->map[i][j] != 'S')
					return (0);
				if ((i == 0 || i == map->res_x - 1 || j == 0 
					|| j == map->res_y - 1) && map->map[i][j] != 1)
					return (0);
			}
			else
				return (0);
			j++;
		}
		i++;
	}
	if (count == 0)
		return (0);
	return (1);
}
