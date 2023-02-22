/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:17:49 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/22 09:05:48 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p.h"

void	*ft_calloc(size_t i)
{
	size_t	l;
	void	*ptr;

	l = 0;
	ptr = malloc(i + 1);
	if (!ptr)
		return (NULL);
	while (l < i + 1)
	{
		((char *)ptr)[l] = 0;
		l++;
	}
	return (ptr);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*r;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	r = malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = 0;
	return (r);
}

char	*join_helper(char *s1, char *s2, int i, int j)
{
	char	*r;

	r = malloc(sizeof(char) * (i + j + 1));
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		r[i] = s2[j];
		i++;
		j++;
	}
	r[i] = s2[j];
	return (r);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	return (join_helper(s1, s2, i, j));
}

void	f_perror(void)
{
	printf("Error\n");
	exit(0);
}
