/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:59:37 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 08:30:35 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p.h"

int	check_filename(char *name, char *exte)
{
	int	i;
	int	j;

	i = 0;
	while (name[i])
		i++;
	i -= 4;
	if (i < 0)
		return (0);
	j = 0;
	while (exte[j] && name[i] && exte[j] == name[i])
	{
		j++;
		i++;
	}
	if (name[i] || exte[j])
		return (0);
	return (1);
}

void	ft_free(char *str, char **arr)
{
	int	i;

	if (str)
	{
		free(str);
		str = NULL;
	}
	if (arr)
	{
		i = -1;
		while (arr[++i])
			free(arr[i]);
		free(arr);
		arr = NULL;
	}
}

void	m_parsing_heler(t_pd *pd)
{
	while (pd->i_b[pd->i] == '\n' || pd->i_b[pd->i] == ' ')
	{
		if (pd->i_b[pd->i] == ' ')
		{
			if (!check_empty(&pd->i_b[pd->i]))
				break ;
		}
		pd->i++;
	}
}

int	exit_game(void)
{
	exit(0);
	return (1);
}
