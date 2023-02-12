#include "../p.h"
#include "d.h"

void    put_lines(t_inf *inf, t_pd pd)
{
    int i;
    int j;

    i = 60;
    j = 60;
    while (i < 60 * pd.max_width)
    {
        j = 60;
        while (j < 60 * pd.max_height)
        {
            if (!(j % 60) || !(i % 60))
                mlx_pixel_put(inf->mlx, inf->win_ptr, i, j, create_trgb(100, 32, 32, 32));
            j++;
        }
        i++;
    }
}

void    put_player(t_inf *inf, t_pd *pd, int m)
{
    int i;
    int j;
    int f;
    int t;
    int t2;

    i = 0;
    j = 0;
    f = 0;
    while (pd->map[j])
    {
        i = 0;
        while (pd->map[j][i])
        {
            if (pd->map[j][i] == 'N') // check later;
            {
                i = i * 60;
                inf->pi = i;
                j = j * 60;
                inf->pj = j;
                f = 1;
                break;
            }
            i++;
        }
        if (f)
            break;
        j++;
    }
    t = inf->pi;
    t2 = inf->pj;
    while (j < pd->max_height * 60 && j < t2 + 5)
    {
        i = t;
        while (i < pd->max_width * 60 && i < t + 5)
        {
            if (m)
                mlx_pixel_put(inf->mlx, inf->win_ptr, i, j, create_trgb(0, 255, 0, 0));
            else
                mlx_pixel_put(inf->mlx, inf->win_ptr, i, j, create_trgb(0, 192, 192, 192));
            i++;
        }
        j++;
    }
}

void    set_fov(t_inf *inf)
{
}