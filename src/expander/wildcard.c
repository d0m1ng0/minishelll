/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:42:39 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/29 22:22:55 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	init_wc(t_wc *wc, int status)
{
	wc->status = status;
	wc->matches = NULL;
}

static void	ft_strswap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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
			j++;
		}
		i++;
	}
}

t_wc	expand_wildcard(char *pattern)
{
	t_wc			res;
	DIR				*dir;
	struct dirent	*entry;

	init_wc(&res, 0);
	dir = opendir(".");
	if (!dir)
	{
		res.status = 2;
		return (perror("minishell: wildcard"), res);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		else if (match(pattern, entry->d_name))
		{
			if (add_to_array(&res.matches, entry->d_name))
				return (closedir(dir), free_split(res.matches),
					init_wc(&res, 2), res);
		}
		entry = readdir(dir);
	}
	if (res.matches)
		sort_matches(res.matches);
	return (closedir(dir), res);
}

int	expand_wildcards(t_cmd *cmd)
{
	t_wc		wc;
	int			i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			if (has_wildcard(cmd->argv[i]))
			{
				wc = expand_wildcard(cmd->argv[i]);
				if (wc.status == 2)
					return (free_split(wc.matches), 1);
				if (wc.matches && wc.status != 2)
				{
					cmd->argv = insert_into_argv(cmd->argv, wc.matches, i);
					free_split(wc.matches);
					continue ;
				}
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
