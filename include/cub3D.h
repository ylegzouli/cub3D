/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:07:32 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/16 20:00:07 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft.h"
# include "../lib/gnl/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define LARGEUR_SCREEN 800
# define HAUTEUR_SCREEN 600
# define LARGEUR_CHAMP 60
# define SIZE_WALL 50
# define NB_TEXTURE 5

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

/*
**-----------------------------------------------------------------------------------
*/

typedef struct			s_point
{
	double	x;
	double	y;
}						t_point;

typedef struct			s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}
						t_color;

typedef struct			s_image
{
	void    *img;
    void    *data;
    int     bpp;
    int     size;
    int     en;
}						t_image;
/*
**-----------------------------------------------------------------------------------
*/

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
	double	dist_screen;
}						t_map;

typedef struct			s_player
{
	t_point	pos;
	t_point	v0;
	t_point	v1;
}						t_player;

typedef struct			s_raycast
{
	t_point	angle;
	double	tan;

	double	tmp_x;
	double	tmp_y;
	double   Ya;
	double   Xa;
	t_point	A;
	t_point	B;

	double	total_angle;
	double	dist_wall;
	double	wall;
}						t_raycast;

typedef struct			s_mlx
{
	void	*ptr;
	void	*win;
	t_image	*img;
	t_image	*xpm_img[NB_TEXTURE];
}
						t_mlx;

typedef	struct			s_hook
{
	t_mlx		*mlx;
	t_raycast 	*ray;
	t_map		*map;
	t_player	*player;
}						t_hook;

/*
**----------------------------------- START ------------------------------------------
*/

void		ft_print_debugage(/*t_parse *data, */t_map *map, t_player *player, t_raycast *ray);
void		init_mlx(t_mlx *mlx);
void		init_data(t_parse **data, t_map **map, t_player **player, t_raycast **ray, t_mlx **mlx, t_hook **hook);

/*
**---------------------------------- PARSING -----------------------------------------
*/

void		parse_file(char **av, t_parse **data, t_map **map, t_player **player);
void		parse_res(t_list *li, t_parse **data);
void		parse_tex(t_list *li, t_parse **data);
void		parse_color(t_list *li, t_parse **data);
void		parse_map(t_list *li, t_map **map );
void		parse_player(t_map *map, t_player **player);
void		get_case(t_player **player, char tmp, int i, int j);
void		get_size_map(t_list *li, t_map **map);

/*
**----------------------------------- CHECK -------------------------------------------
*/

/*
**----------------------------------- RAYCAST -----------------------------------------
*/

void		raycast(t_map *map, t_player *player, t_raycast **ray);
void		get_ray_angle(int x, t_player *player, t_map *map, t_raycast *ray);
void		inter_x(t_map *map, t_player *player, t_raycast **ray);
void		inter_x2(t_map *map, t_raycast **raycast);
void		inter_y(t_map *map, t_player *player, t_raycast **ray);
void		inter_y2(t_map *map, t_raycast **raycast);
void		distance_mur(t_player *player, t_raycast **ray);
int			transfer_coords_x(t_map *map, double x);
int			transfer_coords_y(t_map *map, double y);

/*
**---------------------------------- AFFICHAGE ----------------------------------------
*/

void		affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player);
void		draw_column(t_mlx *mlx, t_raycast *ray, int x);
//void		draw_floor();
//void		draw_ceil();

/*
**----------------------------------- EVENT -------------------------------------------
*/

int			hook_keydown(int key, t_hook *hook);
void		rotate_player(t_player *player, int key, double angle);
void		move_player(t_player *player, int key, t_map *map);
//void		exit(t_hook *hook);
//--> free toutes les data, puis exit (a utiliser aussi en cas d'erreur)

/*
**----------------------------------- IMAGE -------------------------------------------
*/

t_image		*new_image(t_mlx *mlx, int l, int h);
//t_image		*new_xpm_image(t_mlx *mlx, char *xpm, int l, int h);
void		put_pixel(t_image *img, int x, int y, int color);
//void		get_pixel(t_mlx *mlx, int x, int y);
void		clear_image(t_image *img, int l, int h);
//void		destroy_image(t_image *img);

/*
**---------------------------------- TEXTURE ------------------------------------------
*/

//void		init_texture(t_parse *data, t_mlx *mlx);
//void		convert_color(t_parse *data);

/*
**----------------------------------- OTHER -------------------------------------------
*/

int		is_id(char *line);
int		is_map_line(char *line);
void	vect_mult(t_player *player);

/*
**-------------------------------------------------------------------------------------
*/
#endif