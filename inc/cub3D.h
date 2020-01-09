/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:07:32 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/09 19:55:50 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft.h"
# include "../lib/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define LARGEUR_SCREEN 1000
# define HAUTEUR_SCREEN 800

# define LARGEUR_CHAMP 60
# define SIZE_WALL 60
# define NB_TEXTURE 5

#  define K_ESC			53
#  define K_UP			126 //
#  define K_DOWN		125
#  define K_LEFT		123
#  define K_RIGHT		124
/*
**-------------------------------------------------------------------------------
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
}						t_color;

typedef struct			s_image
{
	void    *img;
    void    *data;
    int     bpp;
    int     size;
    int     en;
	int		l;
	int		h;
}						t_image;
/*
**-------------------------------------------------------------------------------
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
	int		res_x;
	int		res_y;
	int		size_x;
	int		size_y;
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
	double	Ya;
	double	Xa;
	t_point	A;
	t_point	B;

	t_point	sprA;
	t_point	sprB;
	double	dist_spr;
	double	sprite;
	int		spr_color;
	int		spr_x;

	
	char	tex;
	int		tex_x;
	int		tex_y;
	int		color;
	int		floor;
	int		ceil;
	double	total_angle;
	double	dist_wall;
	double	wall;
}						t_raycast;

typedef struct			s_mlx
{
	int		res_x;
	int		res_y;
	void	*ptr;
	void	*win;
	t_image	*img;
	t_image	*xpm_img[NB_TEXTURE];
	t_image	*spr_img;
}						t_mlx;

typedef	struct			s_hook
{
	t_mlx		*mlx;
	t_raycast 	*ray;
	t_map		*map;
	t_player	*player;
}						t_hook;
/*
**---------------------------------- START ----------------------------------------
*/
void		ft_print_debugage(/*t_parse *data, */t_map *map, t_player *player, t_raycast *ray);

int			start(t_mlx *mlx, t_parse *data, int ac, char **av);
int			init_data(t_map **map, t_player **player, t_mlx **mlx, t_hook **hook);
int			init_data2(t_parse **data, t_raycast **ray, t_hook **hook);
int			init_mlx(t_mlx *mlx, t_parse *data);
/*
**--------------------------------- PARSING ---------------------------------------
*/
int			parse_file(char **av, t_parse **data, t_map **map, t_player **player);
void		parse_res(t_list *li, t_parse **data, t_map *map);
void		parse_tex(t_list *li, t_parse **data);
void		parse_color(t_list *li, t_parse **data);
void		parse_map(t_list *li, t_map **map );
void		parse_player(t_map *map, t_player **player);
void		get_case(t_player **player, char tmp, int i, int j);
void		get_size_map(t_list *li, t_map **map);
/*
**--------------------------------- RAYCAST ----------------------------------------
*/
void		raycast(t_map *map, t_player *player, t_raycast **ray);
void		get_ray_angle(int x, t_player *player, t_map *map, t_raycast *ray);
void		inter_x(t_map *map, t_raycast **ray);
void		inter_x2(t_map *map, t_raycast **raycast);
void		inter_y(t_map *map, t_raycast **ray);
void		inter_y2(t_map *map, t_raycast **raycast);
void		distance_mur(t_player *player, t_raycast **ray);
int			transfer_coords_x(t_map *map, double x);
int			transfer_coords_y(t_map *map, double y);
/*
**--------------------------------- AFFICHAGE --------------------------------------
*/
void		affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player);
void		draw_column(t_mlx *mlx, t_raycast *ray, int x);
//void		draw_map(t_mlx *mlx, t_player *player, t_map *map);
/*
**---------------------------------- EVENT -----------------------------------------
*/
int			hook_keydown(int key, t_hook *hook);
void		rotate_player(t_player *player, int key, double angle);
void		move_player(t_player *player, int key, t_map *map);
int			exit_all(t_hook *hook);
/*
**---------------------------------- IMAGE -----------------------------------------
*/
t_image		*new_image(t_mlx *mlx, int l, int h);
t_image		*new_xpm_image(t_mlx *mlx, char *xpm);
t_image		*new_png_image(t_mlx *mlx, char *png);
void		put_pixel(t_image *img, int x, int y, int color);
int			get_pixel(t_image *img, int x, int y);
void		clear_image(t_image *img, int l, int h);
void		destroy_image(t_image *img, t_mlx *mlx);
/*
**--------------------------------- TEXTURE ----------------------------------------
*/
int			init_texture(t_parse *data, t_mlx *mlx);
void		get_texture(t_raycast *ray, t_mlx *mlx, int x, int y);
void		get_texture_fnc(t_raycast *ray, t_parse *data);
void        get_texture_spr(t_raycast *ray, t_mlx *mlx, int x, int y);
/*
**--------------------------------- SPRITE ----------------------------------------
*/
void        dist_spr(t_raycast *ray, t_map *map);
void        draw_spr_column(t_raycast *ray, t_map *map, t_mlx *mlx, int x);
/*
**----------------------------------- BMP ------------------------------------------
*/
void		opt_save_bmp(t_mlx *mlx, int ac, char **av);
void		int_to_char(char *str, int nb);
void		save_bitmap(char *filename, t_mlx *mlx);
void		bitmap_image(t_mlx *mlx, int fd);
/*
**----------------------------------- OTHER ----------------------------------------
*/
int			is_id(char *line);
int			is_map_line(char *line);
int			check_map(t_map *map);
void		vect_mult(t_player *player);
void		ft_free_split(char **split);
//void		draw_pos(t_mlx *mlx, t_map *map, t_player *player);
/*
**-----------------------------------------------------------------------------------
*/
#endif