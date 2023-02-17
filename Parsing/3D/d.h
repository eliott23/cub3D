#ifndef D_H
#define D_H
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include "../p.h"

#define tile_size 60

typedef struct s_img
{
	void	*img_ptr;
	char	*adrr;
	int		bpp; //bits per pixel
	int		size_line;
	int		endian;
} t_img; 

typedef struct inf{
    void    *win_ptr;
    void    *mlx;
    t_img   img;
    int     *p_w;
    int     *p_h;
    void    *player;
    double     pi;
    double     pj;
    double  fov; 
    t_pd    *pd;
    int     step;
    double  h_i;
    double  h_j;
    double  v_i;
    double  v_j;
    double  col_dist;
    double  o_col_dist;
    int     flag;
}   t_inf;
void    put_point(t_inf *inf, double i, double j, int m);
void    put_player(t_inf *inf, t_pd *pd, int m);
int	    create_trgb(int t, int r, int g, int b);
void    put_lines(t_inf *inf, t_pd pd);
void	my_mlx_pixel_put(t_inf *data, int x, int y, int color);
void    redisplay_view(t_inf *inf, int keycode);
void    redisplay_move(double new_i, double new_j, t_inf *inf);
#endif 