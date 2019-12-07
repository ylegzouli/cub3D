#include "cub3D.h"

void		init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, LARGEUR_SCREEN, HAUTEUR_SCREEN, "cub3D");
}


int		hook_keydown(int key, t_hook *hook)
{
	if (key == K_LEFT)
	{
		hook->player->angle = hook->player->angle + 1;
	}
	if (key == K_RIGHT)
	{	
		hook->player->angle = hook->player->angle - 1;
	}
	if (hook->player->angle == 361)
        hook->player->angle = 1;
    if (hook->player->angle == -1)
        hook->player->angle = 359;
//	if (key == K_UP || key == K_DOWN)
//		move_player(hook->player, key, hook->player->angle);
//	if (key == K_DOWN) 
//	if (key == K_ESC)
	affichage(hook->mlx, hook->ray, hook->map, hook->player);
	ft_print_debugage(hook-> map, hook->player, hook->ray);
//	mlx_string_put(mlx->ptr, mlx->win, 10, 10, 255000, "");
//	printf("x: %f\ny: %f\n-----------------------\nangle: %f\n", hook->player->pos.x, hook->player->pos.y, hook->player->angle);
	return (0);
}

void		move_player(t_player *player, int key, float angle)
{
	float	tmp_angle;
	tmp_angle = (angle * 3.14) / 180;
	if ((angle) >= 0 && (angle) < 90)
	{
		if (key == K_UP)
		{	
			player->pos.y = player->pos.y + sin(tmp_angle) * 0.2;
			player->pos.x = player->pos.x + cos(tmp_angle) * 0.2;
		}
		if (key == K_DOWN)
		{
			player->pos.y = player->pos.y - sin(tmp_angle) * 0.2;
			player->pos.x = player->pos.x - cos(tmp_angle) * 0.2;
		}
	}
	if ((angle) >= 90 && (angle) <= 180)
	{
		if (key == K_UP)
		{
			player->pos.y = player->pos.y + sin(tmp_angle) * 0.2;
			player->pos.x = player->pos.x - cos(tmp_angle) * 0.2;
		}
		if (key == K_DOWN)
		{
			player->pos.y = player->pos.y - sin(tmp_angle) * 0.2;
			player->pos.x = player->pos.x + cos(tmp_angle) * 0.2;
		}
	}
	if ((angle) > 180 && (angle) < 270)
	{
		if (key == K_UP)
		{	
			player->pos.y = player->pos.y - sin(tmp_angle) * 0.2;
			player->pos.x = player->pos.x - cos(tmp_angle) * 0.2;
		}
		if (key == K_DOWN)
		{
			player->pos.y = player->pos.y + sin(tmp_angle) * 0.2;
			player->pos.x = player->pos.x + cos(tmp_angle) * 0.2;
		}
	}
	if ((angle) >= 270 && (angle) < 360)
	{
		if (key == K_UP)
		{	
			player->pos.x = player->pos.x + cos(tmp_angle) * 0.2;
			player->pos.y = player->pos.y - sin(tmp_angle) * 0.2;
		}
		if (key == K_DOWN)
		{
			player->pos.x = player->pos.x - cos(tmp_angle) * 0.2;
			player->pos.y = player->pos.y + sin(tmp_angle) * 0.2;
		}
	}
}

void		affichage(t_mlx *mlx, t_raycast *ray, t_map *map, t_player *player )
{
	int		x;
	float	angle;
	float	tmp;

	x = 0;
	tmp = (float)LARGEUR_CHAMP / (float)LARGEUR_SCREEN;
	mlx->img = mlx_new_image(mlx->ptr, LARGEUR_SCREEN, HAUTEUR_SCREEN);
	mlx->data = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->size), &(mlx->en));
	mlx->bpp = mlx->bpp / 8;
	while (x < LARGEUR_SCREEN)
	{
		angle = player->angle + (((float)LARGEUR_SCREEN / 2) - x) * tmp;
		if (angle == 0)
		{
			angle = 360;
		}
		raycast(map, player, &ray, angle);
		draw_column(mlx, ray, x);
		x++;
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





