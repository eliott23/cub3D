#ifndef D_H
#define D_H
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include "../p.h"

typedef struct inf{
    void    *win_ptr;
    void    *mlx;
    int     *p_w;
    int     *p_h;
    void    *player;
    int     pi;
    int     pj;
    double  fov; 
    t_pd    *pd;
}   t_inf;
void    put_player(t_inf *inf, t_pd *pd);
int	create_trgb(int t, int r, int g, int b);
void    put_lines(t_inf *inf, t_pd pd);
#endif 