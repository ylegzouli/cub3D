#include "cub3D.h"

int		is_id(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (1);
	if (line[0] == 'N' && line[1] == 'O')
		return (2);
	if (line[0] == 'S' && line[1] == 'O')
		return (3);
	if (line[0] == 'W' && line[1] == 'E')
		return (4);
	if (line[0] == 'E' && line[1] == 'A')
		return (5);
	if (line[0] == 'S' && line[1] == ' ')
		return (6);
	if (line[0] == 'F' && line[1] == ' ')
		return (7);
	if (line[0] == 'C' && line[1] == ' ')
		return (8);
	else
		return (0);
}

int		is_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == '1')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

void	get_size_map(t_list *li)
{
}

void	ft_print_debugage(t_parse *data, t_map *map, t_list *li, t_list *tmp)
{
	int	i;
/*	printf("__________________ DATA ______________________\n");
	
	printf("couleur rouge sol: %d\n", data->sol->r);
	printf("couleur vert  sol: %d\n", data->sol->g);
	printf("couleur bleu  sol: %d\n", data->sol->b);
	printf("\n");
	printf("couleur rouge plafond: %d\n", data->plafond->r);
	printf("couleur vert  plafond: %d\n", data->plafond->g);
	printf("couleur bleu  plafond: %d\n", data->plafond->b);
	printf("\n");
	printf("\n");
	printf("resolution x: %d\n", data->res_x);
	printf("resolution y: %d\n", data->res_y);
	printf("\n");
	printf("texture nord: %s\n", data->tex_no);
	printf("texture sud : %s\n", data->tex_su);
	printf("texture west: %s\n", data->tex_we);
	printf("texture east: %s\n", data->tex_ea);
	printf("\n");
	printf("texture sprite: %s\n", data->tex_no);
	printf("\n");
	printf("\n");
	
	printf("__________________ MAP ______________________\n");

	i = 0;
	printf("size map x: %d\n", map->size_x);
	printf("size map y: %d\n", map->size_y);
	printf("\n");
	while (i < map->size_y)
	{
		printf("%s\n", (map->map)[i]);
		i++;
	}
	printf("\n");
*/	printf("__________________ LISTE ______________________\n");

	i = 0;	
	printf("tmp %d: %s\n", i, tmp->content);
	printf("\n");
	while (li != NULL)
	{
		printf("line %d: %s --- len : %d\n", i, li->content, ft_strlen(li->content));
		li = li->next;
		i++;
	}
//	printf("line %d: %s\n", i, li->content);
	printf("\n");
	printf("_______________________________________________\n");
	
	

}
