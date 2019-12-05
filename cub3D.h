/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:07:32 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/04 14:35:14 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./lib/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "./lib/gnl/get_next_line.h"

# define LARGEUR_SCREEN 320
# define HAUTEUR_SCREEN 200
# define LARGEUR_CHAMP 60
# define ANGLE_RAY (60/320) 
# define SIZE_WALL 64

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

typedef struct			s_point
{
	float	x;
	float	y;
}						t_point;

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
	float	dist_screen;
}						t_map;

typedef struct			s_player
{
	t_point	pos;
	t_point	vec;
	float	angle;
}						t_player;

typedef struct			s_raycast
{
	float	tmp_x;
	float	tmp_y;
	float   Ya;
	float   Xa;
	t_point	A;
	t_point	B;

	float	dist_wall;
	float	wall;
}						t_raycast;

void    	ft_print_debugage(t_parse *data, t_map *map, t_player *player, t_raycast *ray);
void        init_data(t_parse **data, t_map **map, t_player **player, t_raycast **ray);

void        parse_file(char **av, t_parse **data, t_map **map, t_player **player);
void        parse_res(t_list *li, t_parse **data);
void        parse_tex(t_list *li, t_parse **data);
void        parse_color(t_list *li, t_parse **data);
void        parse_map(t_list *li, t_map **map );
void        parse_player(t_map *map, t_player **player);

void        raycast(t_map *map, t_player *player, t_raycast **ray, float angle);
void		inter_x(t_map *map, t_player *player, t_raycast **ray, float angle);
void        inter_x2(t_map *map, t_raycast **raycast);
void        inter_y(t_map *map, t_player *player, t_raycast **ray, float angle);
void        inter_y2(t_map *map, t_raycast **raycast);
void        distance_mur(t_player *player, t_raycast **ray, float angle);

int     	is_id(char *line);
int    		is_map_line(char *line);
void    	get_size_map(t_list *li, t_map **map);
void    	get_case(t_player **player, char tmp, int i, int j);
//void		rotate_player(t_player **player, float angle);

#endif
