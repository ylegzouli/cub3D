#include "../include/cub3D.h"

int		hook_keydown(int key, t_hook *hook)
{
	printf("%d\n", key);
	if (key == K_LEFT || key == K_RIGHT)
		rotate_player(hook->player, key, 5);
	if (key == K_UP || key == K_DOWN)
		move_player(hook->player, key, hook->map);
//	if (key == K_ESC)
//		return (exit_all(hook));
	affichage(hook->mlx, hook->ray, hook->map, hook->player);
//	ft_print_debugage(hook->map, hook->player, hook->ray);
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

void		move_player(t_player *player, int key, t_map *map)
{
	double	x;
	double	y;
	double	tmp_x;
	double	tmp_y;

	tmp_x = (player->pos.x * SIZE_WALL) + ((0.3 * player->v1.x) * SIZE_WALL);
	tmp_y = (player->pos.y * SIZE_WALL) + ((0.3 * player->v1.y) * SIZE_WALL);
	x = player->pos.x + 0.3 * player->v1.x;
	y = player->pos.y + 0.3 * player->v1.y;
	if (key == K_DOWN)
	{
		if (map->map[(int)(player->pos.y * SIZE_WALL) / SIZE_WALL][(int)tmp_x / SIZE_WALL] != '1')
			player->pos.x = x;
		if (map->map[(int)tmp_y / SIZE_WALL][(int)(player->pos.x * SIZE_WALL) / SIZE_WALL] != '1')
			player->pos.y = y;
	}
	tmp_x = (player->pos.x * SIZE_WALL) - ((0.3 * player->v1.x) * SIZE_WALL);
	tmp_y = (player->pos.y * SIZE_WALL) - ((0.3 * player->v1.y) * SIZE_WALL);
	x = player->pos.x - 0.3 * player->v1.x;
    y = player->pos.y - 0.3 * player->v1.y;
	if (key == K_UP)
	{
		if (map->map[(int)(player->pos.y * SIZE_WALL) / SIZE_WALL][(int)tmp_x / SIZE_WALL] != '1')
			player->pos.x = x;
		if (map->map[(int)tmp_y / SIZE_WALL][(int)(player->pos.x * SIZE_WALL) / SIZE_WALL] != '1')
			player->pos.y = y;
	}
}

int			exit_all(t_hook *hook)
{
	int		i;

	i = 0;
	while (i < NB_TEXTURE)
	{
		destroy_image(hook->mlx->xpm_img[i], hook->mlx->ptr);
		i++;
	}
	destroy_image(hook->mlx->img, hook->mlx->ptr);
	mlx_destroy_window(hook->mlx->ptr, hook->mlx->win);
	free(hook);
	return (0);
}
