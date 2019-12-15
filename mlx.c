#include "cub3D.h"

void		init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, LARGEUR_SCREEN, HAUTEUR_SCREEN, "cub3D");
}

int		hook_keydown(int key, t_hook *hook)
{
	if (key == K_LEFT || key == K_RIGHT)
		rotate_player(hook->player, key, 5);
	if (key == K_UP || key == K_DOWN)
		move_player(hook->player, key);
//	if (key == K_DOWN) 
//	if (key == K_ESC)
	affichage(hook->mlx, hook->ray, hook->map, hook->player);
	ft_print_debugage(hook-> map, hook->player, hook->ray);
	return (0);
}

void		rotate_player(t_player *player, int key, double angle)
{
	double	x;
	double	y;

	x = player->v1.x;
	y = player->v1.y;
	if (key == K_RIGHT)
	{
		player->v1.x = x * cos((-angle * M_PI) / 180) + y * sin((-angle * M_PI) / 180);
		player->v1.y = (-x * sin((-angle * M_PI) / 180)) + y * cos((-angle * M_PI) / 180);
	}
	if (key == K_LEFT)
	{
		player->v1.x = x * cos((angle * M_PI) / 180) +y * sin((angle * M_PI) / 180);
		player->v1.y = (-x * sin((angle * M_PI) / 180)) + y * cos((angle * M_PI) / 180);
	}
}

void		move_player(t_player *player, int key)
{
	if (key == K_DOWN)
	{
		player->pos.x = player->pos.x + 0.5 *player->v1.x;
		player->pos.y = player->pos.y + 0.5 *player->v1.y;
	}
	if (key == K_UP)
	{	
		player->pos.x = player->pos.x - 0.5 * player->v1.x;
		player->pos.y = player->pos.y - 0.5 * player->v1.y;
	}
}

void		affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player )
{
	int		x;
	double	angle;
	double	tmp;

	x = 0;
	tmp = (double)LARGEUR_CHAMP / (double)LARGEUR_SCREEN;
	mlx->img = mlx_new_image(mlx->ptr, LARGEUR_SCREEN, HAUTEUR_SCREEN);
	mlx->data = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->size), &(mlx->en));
	mlx->bpp = mlx->bpp / 8;
	vect_mult(player);
	while (x < LARGEUR_SCREEN)
	{
		get_ray_angle(x, player, map, ray);
		raycast(map, player, &ray);
		draw_column(mlx, ray, x);
		x++;
		if (x < LARGEUR_SCREEN / 2)
			ray->total_angle =  -(x - LARGEUR_SCREEN / 2) * tmp;
		else
			ray->total_angle = (x - LARGEUR_SCREEN / 2) * tmp;

	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

void		draw_column(t_mlx *mlx, t_raycast *ray, int x)
{
	int		y;
	int		start;
	int		end;

	start = (HAUTEUR_SCREEN - ray->wall) / 2;
	end = start + ray->wall;
	if (start < 0)
		start = 0;
	if (end > HAUTEUR_SCREEN - 1)
		end = HAUTEUR_SCREEN - 1;
	y = start; 
	while (y < end)
	{
		put_pixel(mlx, x, y, 100);
		y++;
	}
}

void		put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= LARGEUR_SCREEN || y >= HAUTEUR_SCREEN))
	{	
		*(int *)(mlx->data + ((x + y * LARGEUR_SCREEN) * mlx->bpp)) = 16711680;
	}
}
