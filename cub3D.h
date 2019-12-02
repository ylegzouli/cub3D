#ifndef CUB3D_H
# define CUB3D_H

#include "./lib/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./lib/gnl/get_next_line.h"

/*			IDENTIFIANT:
**	R  = 1
**	NO = 2
**	SO = 3
**	WE = 4
**	EA = 5
**	S  = 6
**	F  = 7
**	C  = 8
*/

typedef struct			s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}						t_color;

typedef struct			s_parse
{
	int		res_x;
	int		res_y;

	char	*tex_no;
	char	*tex_su;
	char	*tex_we;
	char	*tex_ea;

	char	*tex_spr;
	t_color	sol;
	t_color	plafond;
}						t_parse;

typedef	struct			s_map
{
	size_t	size_x;
	size_t	size_y;
	char	**map;
}						t_map;

void    	ft_print_debugage(t_parse *data, t_map *map, t_list *li, t_list *tmp);

void        parse_file(char **av, t_parse **data, t_map **map);
void        parse_res(t_list *li, t_parse **data);
void        parse_tex(t_list *li, t_parse **data);
void        parse_color(t_list *li, t_parse **data);
void        parse_map(t_list **li, t_map **map );

int     	is_id(char *line);
int    		is_map_line(char *line);
void    	get_size_map(t_list *li);


#endif
