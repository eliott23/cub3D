#include "d.h"
int get_start_p(t_inf *inf)
{
    return (450 - (int)((tile_size / inf->col_dist[inf->index]) * 350));
}

void    draw_sma_wlard(t_inf *inf)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 1501)
    {
        j = 0;
        while (j < 450)
        {
            my_mlx_pixel_put(inf, i, j, create_trgb(0, 0, 0, 255), 1);
            j++;
        }
        while (j < 900)
        {
            my_mlx_pixel_put(inf, i, j, create_trgb(0, 128, 128, 128), 1);
            j++;
        }
        i++;
    }
}

void    render_3d(t_inf *inf)
{
    int j;
    int top;
    int t;

    inf->index = 0;
    while (inf->index < 1501)
    {
        j = get_start_p(inf);
        if (j < 0)
            j = 0;
        // while (j < top)
        // {
        //     // if (inf->index > inf->pd->max_width * 10 || j > inf->pd->max_height * 10)
        //         my_mlx_pixel_put(inf, inf->index, j, create_trgb(0, 0, 0, 255), 1);
        //     j++;
        // }
        t = j;
        while (j < 900 - t && j < 900)
        {
            // if (inf->index > inf->pd->max_width * 10 || j > inf->pd->max_height * 10)
            // {
                my_mlx_pixel_put(inf, inf->index, j, create_trgb(0, 0, 255, 255), 1);
            // }
            j++;
        }
        // while (j < 900)
        // {
        //     // if (inf->index > inf->pd->max_width * 10 || j > inf->pd->max_height * 10)
        //         my_mlx_pixel_put(inf, inf->index, j, create_trgb(0, 128, 128, 128), 1);
        //     j++;
        // }
        inf->index++;
    }
    // printf("this is index %d\n", inf->index);
}