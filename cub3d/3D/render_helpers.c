/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 08:13:03 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 05:34:11 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d.h"

// empty or corrupted xpm file, add protection
int	xpm_init(t_inf *inf)
{
	int	i;

	inf->textures[0].img.img_ptr = mlx_xpm_file_to_image(inf->mlx,
			inf->pd->so, &inf->textures[0].width, &inf->textures[0].height);
	inf->textures[1].img.img_ptr = mlx_xpm_file_to_image(inf->mlx,
			inf->pd->no, &inf->textures[1].width, &inf->textures[1].height);
	inf->textures[2].img.img_ptr = mlx_xpm_file_to_image(inf->mlx,
			inf->pd->we, &inf->textures[2].width, &inf->textures[2].height);
	inf->textures[3].img.img_ptr = mlx_xpm_file_to_image(inf->mlx,
			inf->pd->ea, &inf->textures[3].width, &inf->textures[3].height);
	if (!inf->textures[0].img.img_ptr || !inf->textures[1].img.img_ptr
		|| !inf->textures[2].img.img_ptr || !inf->textures[3].img.img_ptr)
	{
		printf("invalid xpm path/file\n");
		return (0);
	}
	i = -1;
	while (++i < 4)
		inf->textures[i].img.adrr = mlx_get_data_addr(
				inf->textures[i].img.img_ptr,
				&inf->textures[i].img.bpp, &inf->textures[i].img.size_line,
				&inf->textures[i].img.endian);
	return (1);
}

int	get_index(t_rays ray)
{
	double	angle;

	angle = fmod(ray.ray_angle, 360);
	if (angle < 0)
		angle = 360 + angle;
	if (ray.h_v == 1)
	{
		if (angle > 180 && angle < 360)
			return (1);
		else if (angle > 0 && angle < 180)
			return (0);
	}
	else
	{
		if (angle > 90 && angle < 270)
			return (3);
		else if (angle < 90 || angle > 270)
			return (2);
	}
	return (-1);
}
//to get the position of the current pixel
//bpp is devided by 8 cus its already multiplied by 8 
//(a pixel is coded on 4 char, those chars worth 8 bits each)
//(X position * 4 + 4 * Line size * Y position)

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;
	char	*pixel;

	offset = y * img->size_line + x * (img->bpp / 8);
	pixel = img->adrr + offset;
	*(unsigned int *)pixel = color;
}

int	get_pixel(t_inf *inf, int i, int y)
{
	int		offset;
	char	*pixel;
	int		j;

	j = get_index(inf->rays[i]);
	offset = y * inf->textures[j].img.size_line
		+ (inf->rays[i].x) * (inf->textures[j].img.bpp / 8);
	pixel = inf->textures[j].img.adrr + offset;
	return (*(int *)pixel);
}

void	outside_map(t_inf *inf)
{
	if (inf->flag == -2)
	{
		inf->rays[inf->index].col_dist = ((inf->v.i - inf->p.i)
				* (inf->v.i - inf->p.i)) + ((inf->v.j - inf->p.j)
				* (inf->v.j - inf->p.j));
		inf->rays[inf->index].col_dist = sqrt(inf->rays[inf->index].col_dist);
		inf->flag = 0;
		inf->rays[inf->index].h_v = 2;
		inf->rays[inf->index].x = fmod(inf->v.j, TILE_SIZE);
	}
	else
	{
		inf->rays[inf->index].col_dist = ((inf->h.i - inf->p.i)
				* (inf->h.i - inf->p.i)) + ((inf->h.j - inf->p.j)
				* (inf->h.j - inf->p.j));
		inf->rays[inf->index].col_dist = sqrt(inf->rays[inf->index].col_dist);
		inf->rays[inf->index].h_v = 1;
		inf->flag = 0;
		inf->rays[inf->index].x = fmod(inf->h.i, TILE_SIZE);
	}	
}
