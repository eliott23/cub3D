/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:34:50 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 08:16:13 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p.h"

int	is_player(char player)
{
	return (player == 'N' || player == 'W' || player == 'E' || player == 'S');
}

int	check_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

void	check_char(char *s)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (s[i])
	{
		if (!is_player(s[i]) && s[i] != '0'
			&& s[i] != '1' && s[i] != ' ' && s[i] != '\n')
			f_perror();
		if (is_player(s[i]))
		{
			if (f)
				f_perror();
			f = 1;
		}
		i++;
	}
	if (!f)
		f_perror();
}

void	check_newl(char *s)
{
	int	i;

	i = 0;
	if (check_empty(s))
		f_perror();
	while (s[i])
	{
		if (s[i] == '\n' && s[i + 1])
		{
			if (check_empty(s + i + 1))
				f_perror();
		}
		i++;
	}
}

void	map_p(t_pd *pd)
{
	int	i;
	int	j;

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
			if (pd->map[i][j] == '0' || is_player(pd->map[i][j]))
				check_position(i, j, pd->map);
			j++;
		}
		i++;
	}
}
