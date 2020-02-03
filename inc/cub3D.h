/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:07:32 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/19 18:13:51 by ylegzoul         ###   ########.fr       */
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
# define LARGEUR_SCREEN 2560
# define HAUTEUR_SCREEN 1400
# define LARGEUR_CHAMP 60
# define SIZE_WALL 60
# define NB_TEXTURE 5

# define K_ESC		53
# define K_UP		126
# define K_DOWN		125
# define K_LEFT		123
# define K_RIGHT	124
# define K_SPACE	49
# define K_C		8
# define K_M		46
# define K_W		13
# define K_A		0
# define K_D		2
# define K_S		1

/*
**------------------------------------------------------------
*/
typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_color
{
	int r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_image
{
	int		res_x;
	void	*img;
	void	*data;
	int		bpp;
	int		size;
	int		en;
	int		l;
	int		h;
}				t_image;

typedef struct	s_sprite
{
	double			x;
	double			y;
	double			dist;
	double			size;
	struct s_sprite	*next;

	double			inv_det;
	double			tmpx;
	double			tmpy;
	int				sx;
	int				sp_x;
	int				sp_y;

	int				cutx;
	int				cuty;
	int				start_y;
	int				end_y;
	int				start_x;
	int				end_x;
}				t_sprite;
/*
**----------------------------------------------------------
*/
typedef struct	s_parse
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
}				t_parse;

typedef	struct	s_map
{
	int		res_x;
	int		res_y;
	int		size_x;
	int		size_y;
	char	**map;
	double	dist_screen;
}				t_map;

typedef struct	s_player
{
	t_point	pos;
	t_point	v0;
	t_point	v1;
	int		arme;
	int		cible;
	int		map;
}				t_player;

typedef struct	s_raycast
{
	t_point		angle;
	double		tan;
	double		tmp_x;
	double		tmp_y;
	double		ya;
	double		xa;
	t_point		a;
	t_point		b;
	char		tex;
	int			tex_x;
	int			tex_y;
	int			color;
	int			floor;
	int			ceil;
	double		total_angle;
	double		dist_wall;
	double		wall;
	t_sprite	*spr;
}				t_raycast;

typedef struct	s_mlx
{
	int		res_x;
	int		res_y;
	void	*ptr;
	void	*win;
	double	tab[3000];
	t_image	*img;
	t_image	*xpm_img[NB_TEXTURE];
	t_image	*spr_img;
	t_image	*arme;
	t_image *cible;
}				t_mlx;

typedef	struct	s_hook
{
	t_parse		*data;
	t_mlx		*mlx;
	t_raycast	*ray;
	t_map		*map;
	t_player	*player;
}				t_hook;
/*
**------------------------ START -------------------------------
*/
int				start(t_mlx *mlx, t_parse *data, int ac, char **av);
void			exit_error(t_hook *hook);
int				check_arg(int ac, char **av);
int				init_data(t_map **map, t_player **player,
t_mlx **mlx, t_hook **hook);
int				init_data2(t_parse **data, t_raycast **ray, t_hook **hook);
int				init_mlx(t_mlx *mlx, t_parse *data);
/*
**---------------------- PARSING ------------------------------
*/
int				parse_file(char **av, t_parse **data,
t_map **map, t_player **player);
int				send_line(t_list *li, t_parse **data, t_map **map);
void			parse_res(t_list *li, t_parse **data, t_map *map);
int				parse_tex(t_list *li, t_parse **data);
int				parse_tex2(char **split, t_parse **data);
int				parse_color(t_list *li, t_parse **data);
int				parse_map(t_list *li, t_map **map);
void			parse_player(t_map *map, t_player **player);
void			get_case(t_player **player, char tmp, int i, int j);
void			get_size_map(t_list *li, t_map **map);

/*
**---------------------- RAYCAST ----------------------------------
*/
void			raycast(t_map *map, t_player *player, t_raycast **ray);
void			get_ray_angle(int x, t_player *player,
t_map *map, t_raycast *ray);
void			inter_x(t_map *map, t_raycast **ray);
void			inter_x2(t_map *map, t_raycast **raycast);
void			inter_y(t_map *map, t_raycast **ray);
void			inter_y2(t_map *map, t_raycast **raycast);
void			distance_mur(t_player *player, t_raycast **ray);
void			distance_mur2(double *dist_a, double *dist_b, t_raycast **ray);
int				transfer_coords_x(t_map *map, double x);
int				transfer_coords_y(t_map *map, double y);
/*
**--------------------- AFFICHAGE ------------------------------
*/
void			affichage(t_mlx *mlx, t_raycast *ray,
t_map *map, t_player *player);
void			draw_column(t_mlx *mlx, t_raycast *ray, int x);
void			draw_opt(t_mlx *mlx, t_player *player, t_map *map);
void			draw_arme(t_mlx *mlx);
void			draw_cible(t_mlx *mlx);
void			draw_map(t_mlx *mlx, t_player *player, t_map *map);
/*
**----------------------- EVENT ---------------------------------
*/
int				hook_keydown(int key, t_hook *hook);
void			rotate_player(t_player *player, int key, double angle);
void			move_player(t_player *player, int key, t_map *map);
void			move_player2(t_player *player, int key, t_map *map);
void			decal_player(t_player *player, int key, t_map *map);
void			decal_player2(t_player *player, int key, t_map *map);
int				exit_all(t_hook *hook);
/*
**-------------------- IMAGE ----------------------------------
*/
t_image			*new_image(t_mlx *mlx, int l, int h);
t_image			*new_xpm_image(t_mlx *mlx, char *xpm);
void			put_pixel(t_image *img, int x, int y, int color);
int				get_pixel(t_image *img, int x, int y);
void			clear_image(t_image *img, int l, int h);
void			destroy_image(t_image *img, t_mlx *mlx);
/*
**-------------------- TEXTURE ------------------------------
*/
int				init_texture(t_parse *data, t_mlx *mlx);
void			get_texture(t_raycast *ray, t_mlx *mlx, int y);
void			get_texture_fnc(t_raycast *ray, t_parse *data);
int				get_texture_spr(t_sprite *spr, t_mlx *mlx, int x, int y);
void			free_tex(t_parse *data);
/*
**--------------------- SPRITE -----------------------------------
*/
t_sprite		*new_sprite(int x, int y);
void			sprite_add_back(t_sprite *spr, int x, int y);
void			clear_sprite(t_sprite *begin);
void			save_data_spr(t_sprite *sprite, int x, int y);
void			calc_dist_sprite(t_sprite **sprite,
t_player *player, t_map *map);
void			sort_sprite(t_sprite **sprite, t_player *player);
void			swap_sprite(t_sprite *sp, t_sprite *nxt);
void			calc_data_spr(t_sprite *spr, t_player *player, t_map *map);
void			calc_data_spr2(t_sprite *spr, t_map *map);
void			draw_sprite(t_sprite *spr, t_mlx *mlx,
t_player *player, t_map *map);
void			display_sprite(t_sprite *spr, t_mlx *mlx);
int				is_sprite_save(t_sprite *spr, int x, int y);
/*
**---------------------- BMP -------------------------------
*/
void			opt_save_bmp(t_mlx *mlx, t_hook *hook, int ac, char **av);
void			int_to_char(char *str, int nb);
void			save_bitmap(char *filename, t_mlx *mlx);
void			bitmap_image(t_mlx *mlx, int fd);
/*
**--------------------- OTHER -----------------------------------
*/
int				is_id(char *line);
int				is_map_line(char *line);
int				check_map(t_map *map);
int				check_map2(t_map *map, int i, int j);
int				is_good_char(char c);
void			vect_mult(t_player *player);
void			ft_free_split(char **split);
void			draw_square(t_mlx *mlx, int x, int y, int color);
int				malloc_map(t_map **map);
int				check_size_map(char **m, t_map *map);
int				id_empty_line(char *line);
void			exit_key(t_map *map, t_parse *data);
/*
**----------------------------------------------------------
*/
#endif
