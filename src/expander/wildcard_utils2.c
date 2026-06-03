/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 22:19:19 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/03 13:32:23 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	init_wc(t_wc *wc, int status)
{
	wc->status = status;
	wc->matches = NULL;
}

static int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		while (*s1 == '\'' || *s1 == '\"')
			s1++;
		while (*s2 == '\'' || *s2 == '\"')
			s2++;
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return (ft_tolower(*s1) - ft_tolower(*s2));
		s1++;
		s2++;
	}
	while (*s1 == '\'' || *s1 == '\"')
		s1++;
	while (*s2 == '\'' || *s2 == '\"')
		s2++;
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

static int	ft_strcmp_withquotes(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return (ft_tolower(*s1) - ft_tolower(*s2));
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

void	sort_matches(char **arr)
{
	int	i;
	int	j;
	int	cmp;

	i = 0;
	while (arr && arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			cmp = ft_strcmp(arr[i], arr[j]);
			if (cmp > 0)
				ft_strswap(&arr[i], &arr[j]);
			else if (cmp == 0)
			{
				cmp = ft_strcmp_withquotes(arr[i], arr[j]);
				if (cmp > 0)
					ft_strswap(&arr[i], &arr[j]);
			}
			j++;
		}
		i++;
	}
}

char	*strip_pattern(char *pattern)
{
	t_expand	exp;

	if (init_expand(&exp))
		return (NULL);
	while (pattern[exp.i])
	{
		if (handle_quotes(pattern[exp.i], &exp))
		{
			exp.i++;
			continue ;
		}
		if (append_char(&exp, pattern[exp.i]))
			return (NULL);
		exp.i++;
	}
	return (exp.result);
}
