/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:13:23 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/29 20:58:09 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	has_wildcard(char *s)
{
	int			i;
	t_expand	exp;

	exp.state = NO_QUOTE;
	i = 0;
	while (s && s[i])
	{
		handle_quotes(s[i], &exp);
		if (s[i] == '*' && exp.state == NO_QUOTE)
			return (1);
		i++;
	}
	return (0);
}

int	match(char *pattern, char *str)
{
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '*')
	{
		return (match(pattern + 1, str) || (*str && match(pattern, str + 1)));
	}
	if (*pattern == *str)
		return (match(pattern + 1, str + 1));
	return (0);
}

int	ft_arrlen(char	**arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	add_to_array(char ***arr, char *str)
{
	char	**new;
	int		i;
	int		len;

	len = ft_arrlen(*arr);
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (1);
	i = 0;
	while (i < len)
	{
		new[i] = (*arr)[i];
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (free(new), 1);
	new[i + 1] = NULL;
	free(*arr);
	*arr = new;
	return (0);
}

char	**insert_into_argv(char **argv, char **matches, int ind)
{
	int		old_len;
	int		match_len;
	char	**new;
	int		i;
	int		j;

	old_len = ft_arrlen(argv);
	match_len = ft_arrlen(matches);
	new = malloc(sizeof(char *) * (old_len + match_len + 1));
	if (!new)
		return (NULL);
	j = 0;
	i = 0;
	while (j < ind)
	{
		new[j] = argv[j];
		j++;
	}
	while (i < match_len)
		new[j++] = ft_strdup(matches[i++]);
	i = ind + 1;
	while (argv[i])
		new[j++] = argv[i++];
	new[j] = NULL;
	return (free(argv[ind]), free(argv), new);
}
