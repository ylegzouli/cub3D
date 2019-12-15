#include "../include/cub3D.h"

void		put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= LARGEUR_SCREEN || y >= HAUTEUR_SCREEN))
	{
		*(int *)(mlx->data + ((x + y * LARGEUR_SCREEN) * mlx->bpp)) = 16711680;
	}
}
