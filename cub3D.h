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

# define LARGEUR_SCREEN 520
# define HAUTEUR_SCREEN 400
# define LARGEUR_CHAMP 60
# define ANGLE_RAY (60/320) 
# define SIZE_WALL 50

//#  define K_ESC			65307
#  define K_UP			126
#  define K_DOWN		125
#  define K_LEFT		123
#  define K_RIGHT		124

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

/*-----------------------------------------------------------------------------------*/

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

/*-----------------------------------------------------------------------------------*/

#include <mlx.h>

typedef struct			s_mlx
{
    void	*ptr;
    void	*win;
	void	*img;
	void	*data;

	int		bpp;
	int		size;
	int		en;
}						t_mlx;

void        init_mlx(t_mlx *mlx);
void        affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player);
void        draw_column(t_mlx *mlx, t_raycast *ray, int x);
void        put_pixel(t_mlx *mlx, int x, int y, int color);
void        move_player(t_player *player, int key, float angle);

/*-----------------------------------------------------------------------------------*/

typedef	struct		s_hook
{
	t_mlx		*mlx;
	t_raycast 	*ray;
	t_map		*map;
	t_player	*player;
}					t_hook;

int     hook_keydown(int key, t_hook *hook);

/*-----------------------------------------------------------------------------------*/

void    	ft_print_debugage(/*t_parse *data, */t_map *map, t_player *player, t_raycast *ray);
void        init_data(t_parse **data, t_map **map, t_player **player, t_raycast **ray, t_mlx **mlx, t_hook **hook);

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
void		rotate_player(t_player **player, float angle);

#endif
