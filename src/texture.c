#include "../inc/cub3D.h"

int			init_texture(t_parse *data, t_mlx *mlx)
{
	if (!(mlx->xpm_img[0] = new_xpm_image(mlx, data->tex_no)))
		return (0);
	if (!(mlx->xpm_img[1] = new_xpm_image(mlx, data->tex_su)))
		return (0);
	if (!(mlx->xpm_img[2] = new_xpm_image(mlx, data->tex_we)))
		return (0);
	if (!(mlx->xpm_img[3] = new_xpm_image(mlx, data->tex_ea)))
		return (0);
	if (!(mlx->spr_img = new_xpm_image(mlx, data->tex_spr)))
		return (0);
//	mlx->xpm_img[4] = new_xpm_image(mlx, "texture/sky");
//	mlx->xpm_img[5] = new_xpm_image(mlx, "texture/floor");
	return (1);
}

void        get_texture(t_raycast *ray, t_mlx *mlx, int x, int y)
{
	(void)x;
	if (ray->tex == 'S')
    {
		ray->tex_y = ((y - mlx->res_y / 2 + ray->wall / 2) * mlx->xpm_img[1]->h) / ray->wall;
		ray->color = get_pixel(mlx->xpm_img[1], ray->tex_x, ray->tex_y);
  	}
	else if (ray->tex == 'N')
	{
		ray->tex_y = ((y - mlx->res_y / 2 + ray->wall / 2) * mlx->xpm_img[0]->h) / ray->wall;
		ray->color = get_pixel(mlx->xpm_img[0], ray->tex_x, ray->tex_y);
    }
    else if (ray->tex == 'E')
	{
		ray->tex_y = ((y - mlx->res_y / 2 + ray->wall / 2) * mlx->xpm_img[3]->h) / ray->wall;
		ray->color = get_pixel(mlx->xpm_img[3], ray->tex_x, ray->tex_y);
    }
	else if (ray->tex == 'W')
    {
		ray->tex_y = ((y - mlx->res_y / 2 + ray->wall / 2) * mlx->xpm_img[2]->h) / ray->wall;
		ray->color = get_pixel(mlx->xpm_img[2], ray->tex_x, ray->tex_y);
	}
//	if (mlx->xpm_img[4])
//    	ray->ceil = get_pixel(mlx->xpm_img[4], x, y);
//	if (mlx->xpm_img[5])
//		ray->floor = get_pixel(mlx->xpm_img[5], x, y);
}

void		get_texture_fnc(t_raycast *ray, t_parse *data)
{
		ray->ceil = 65536 * data->plafond.r + 256 * data->plafond.g + data->plafond.b;
		ray->floor = 65536 * data->sol.r + 256 * data->sol.g + data->sol.b;
}

void		get_texture_spr(t_raycast *ray, t_mlx *mlx, int	x, int y)
{
	(void)x;
	ray->tex_y = ((y - mlx->res_y / 2 + ray->sprite / 2) * mlx->spr_img->h) / ray->sprite;
	ray->spr_color = get_pixel(mlx->spr_img, ray->tex_x, ray->tex_y);
}
