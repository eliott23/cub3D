/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:58:30 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 08:03:51 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p.h"

int	s_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s2[i])
		return (0);
	return (1);
}

int	element_id(char *s, char **elmnt)
{
	int	i;

	i = 0;
	while (elmnt[i])
	{
		if (s_cmp(elmnt[i], s))
		{
			ft_free(NULL, elmnt);
			return (i);
		}
		i++;
	}
	f_perror();
	ft_free(NULL, elmnt);
	return (-1);
}

void	store_path(t_pd *pd, char *path, int e)
{
	if (e == 0)
		pd->no = path;
	if (e == 1)
		pd->so = path;
	if (e == 2)
		pd->we = path;
	if (e == 3)
		pd->ea = path;
	if (e == 4)
	{
		check_rgb(path);
		pd->floor = ft_split(path, ',');
		free(path);
		valid_rgb(pd->floor);
	}
	if (e == 5)
	{
		check_rgb(path);
		pd->sqef = ft_split(path, ',');
		free(path);
		valid_rgb(pd->sqef);
	}
}

void	s_dup(char *s, t_pd *pd, int e)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	path = malloc(sizeof(char) * (i + 1));
	if (!path)
		f_perror();
	while (j < i)
	{
		path[j] = s[j];
		j++;
	}
	path[j] = 0;
	store_path(pd, path, e);
}

void	m_parsing(t_pd *pd)
{
	int		e;

	pd->i = 0;
	e = 0;
	pd->n = 0;
	while (pd->i_b[pd->i] && pd->n < 6)
	{
		while (pd->i_b[pd->i] == ' ' || pd->i_b[pd->i] == '\n')
			pd->i++;
		if (pd->i && pd->i_b[pd->i - 1] == ' ')
			f_perror();
		e = element_id((pd->i_b) + pd->i, ft_split("NO SO WE EA F C ", ' '));
		check_elmnt_n(1, pd, e);
		skip_to_next(1, pd);
		s_dup(pd->i_b + pd->i, pd, e);
		pd->n++;
		skip_to_next(0, pd);
	}
	m_parsing_heler(pd);
	map_p(pd);
}
