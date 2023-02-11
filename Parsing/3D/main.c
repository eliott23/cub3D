#include "../p.h"
#include "d.h"

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

int main(int ac, char **av)
{
    t_inf   inf;
    t_pd    pd;

    pd = m_function(ac, av);
    inf.mlx = mlx_init();
    inf.win_ptr = mlx_new_window(inf.mlx, pd.max_width * 60, pd.max_height * 60, "3D");
    m_fill(&inf, pd);
    put_player(&inf, pd);
    put_lines(&inf, pd);
    mlx_pixel_put(inf.mlx, inf.win_ptr, 300, 300, create_trgb(0, 255, 0, 0));
    mlx_loop(inf.mlx);
}