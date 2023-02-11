#include "p.h"

// void   check_spaces(t_pd *pd)
// {
//     int     i;
//     int     j;
//     int     k;

//     i = 0;
//     while (pd->map[i])
//     {
//         j = 0;
//         while (pd->map[i][j] == ' ')
//             j++;
//         while (pd->map[i][j])
//         {
//             if (pd->map[i][j] == ' ' && ) 
//                 f_perror();
//             j++;
//         }
//         i++;
//     }
// }

int check_empty(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] == ' ')
        i++;
    if (s[i] == '\n')
        return (1);
    return (0);
}

void    check_char(char *s)
{
    int i;
    int f;

    i = 0;
    f = 0;
    while (s[i])
    {
        if (s[i] != 'N' && s[i] != '\n' && \
        s[i] != 'S' && s[i] != 'E' && s[i] != 'W'\
        && s[i] != '0' && s[i] != '1' && s[i] != ' ')
            f_perror();
        if (s[i] == 'N' ||\
        s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
        {
            if (f)
            {
                fprintf(stderr, "dup player!\n");
                f_perror();
            }
            f = 1;
        }
        i++;
    }
    if (!f)
    {
        fprintf(stderr, "alllaaa asahbe!!\n");
        f_perror();
    }
}

void    check_newl(char *s)
{
    int i;

    i = 0;
    if (check_empty(s))
    {
        fprintf(stderr, "empty line inside the map!\n");
        f_perror();
    }
    while (s[i])
    {
        if (s[i] == '\n' && s[i + 1])
        {
            if (check_empty(s + i + 1))
            {
                printf("went here!\n");
                fprintf(stderr, "empty line inside the map!\n");
                f_perror();
            }
        }
        i++;
    }
}

void    map_p(t_pd *pd)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (!pd->i_b[pd->i])
        f_perror();
    check_char(&pd->i_b[pd->i]);
    check_newl(&pd->i_b[pd->i]);
    pd->map = ft_split(&pd->i_b[pd->i], '\n');
    if (!pd->map)
        f_perror();
    i = 0;
    while (pd->map[i])
    {
        j = 0;
        while (pd->map[i][j])
        {
            if (pd->map[i][j] == '0' || pd->map[i][j] == 'N' || pd->map[i][j] == 'W' || pd->map[i][j] == 'E' || pd->map[i][j] == 'S')
                check_position(i, j, pd->map);
            j++;
        }
        i++;
    }
}