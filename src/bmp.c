#include "../include/cub3D.h"

void			opt_save_bmp(t_mlx *mlx, int ac, char **av)
{
	if (ac == 3)
	{
		if (ft_strncmp("-save", av[2], 5) == 0)
			save_bitmap("screen.bmp", mlx);
	}
}
/*
char			*int_to_char(int nb)
{
	char	tab[20];
	int		i;

	i = 0;
	while (i < sizeof(nb))
	{
		tab[i] = *tmp + i;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
*/
void			save_bitmap(char *filename, t_mlx *mlx)
{
	int			fd;
	t_fheader	file_header;
	t_iheader	img_header;

	ft_memcpy(&file_header.type, "BM", 2);
	file_header.size = mlx->res_x * mlx->res_y * 4 + 54;
//	file_header.reserved1 = 0;
//	file_header.reserved2 = 0;
//	file_header.offset = 54;
//	img_header.size_header = 40;// sizeof(img_header);
//	img_header.width = mlx->res_x;
//	img_header.height = mlx->res_y;
//	img_header.planes = 1;
//	img_header.bit_count = 24;
//	img_header.compression = 0;
//	img_header.image_size = mlx->res_x * mlx->res_y * 4 + 54;
//	img_header.x = 3780;// 2;
//	img_header.y = 3780;// 2;
//	img_header.used = 0;
//	img_header.important = 0;
	fd = open(filename, O_RDWR | O_CREAT, 0666);
	write(fd, &file_header, sizeof(file_header));
//	write(fd, &img_header, sizeof(img_header));
//	bitmap_image(mlx, fd);
	close(fd);
}

void			bitmap_image(t_mlx *mlx, int fd)
{
	int				x;
	int				y;
	int				temp;
	unsigned char	color[3];
	int				*ptr;

	ptr = (int *)mlx->img->data;
	y = mlx->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < mlx->res_x)
		{
			temp = ptr[x + y * mlx->res_x];
			color[0] = temp % 256;
			temp /= 256;
			color[1] = temp % 256;
			temp /= 256;
			color[2] = temp % 256;
//			printf("%c%c%c\n", color[0], color[1], color[2]);
			write(fd, &color, sizeof(color));
			x++;
		}
		y--;
	}
}
