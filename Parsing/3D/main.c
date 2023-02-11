#include "../p.h"
#include "d.h"

int calc_cord(double angle, int l, int j, int i, t_pd *pd)
{
    if (!pd->map[j / 60])
        return (0);
    if (pd->map[j / 60][i / 60] == '1')
        return (0);
    return (1);
}

void    ray(t_inf *inf, double angle, t_pd *pd, int m)
{
    int l = 0;
    int t = inf->pi;
    int t2 = inf->pj;

    while (calc_cord(angle, l, t2, t, pd))
    {
        t =  inf->pi + (l * cos(angle));
        t2 = inf->pj + (l * sin(angle));
        if (m)
            mlx_pixel_put(inf->mlx, inf->win_ptr, t, t2, create_trgb(50, 255, 0, 0));
        else if ((t % 60) && (t2 % 60)) 
            mlx_pixel_put(inf->mlx, inf->win_ptr, t, t2, create_trgb(50, 192, 192, 192));
        else
            mlx_pixel_put(inf->mlx, inf->win_ptr, t, t2, create_trgb(100, 32, 32, 32));
        l++;
    }
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void    m_fill(t_inf *inf, t_pd pd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < pd.max_height * 60)
    {
        i = 0;
        while (i < pd.max_width * 60)
        {
            if (!pd.map[j / 60][i / 60])
                break;
            if (pd.map[j / 60][i / 60] == '0' || pd.map[j / 60][i / 60] == 'N') //check later;
                mlx_pixel_put(inf->mlx, inf->win_ptr, i, j, create_trgb(0, 192, 192, 192));
            else
                mlx_pixel_put(inf->mlx, inf->win_ptr, i, j, create_trgb(0, 32, 32, 32));
            i++;
        }
        j++;
    }
}

void    put_rays()
{

}

double  deg_to_rad(double angle)
{
    angle = angle * (M_PI / 180);
    return (angle);
}

int main(int ac, char **av)
{
    t_inf   inf;
    t_pd    pd;

    inf.fov = 90;
    pd = m_function(ac, av);
    inf.mlx = mlx_init();
    inf.win_ptr = mlx_new_window(inf.mlx, pd.max_width * 60, pd.max_height * 60, "3D");
    m_fill(&inf, pd);
    put_player(&inf, &pd);
    put_lines(&inf, pd);
    ray(&inf, deg_to_rad(5), &pd, 1);
    mlx_loop(inf.mlx);
}