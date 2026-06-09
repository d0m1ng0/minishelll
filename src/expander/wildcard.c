/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:42:39 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 16:12:36 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static DIR	*open_wc_dir(t_wc *res)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
	{
		perror("minishell: wildcard");
		res->status = 2;
	}
	return (dir);
}

static int	handle_entry(t_wc *res, struct dirent *entry, char *pattern)
{
	if (entry->d_name[0] == '.' && pattern[0] != '.')
		return (0);
	if (match(pattern, entry->d_name))
	{
		if (add_to_array(&res->matches, entry->d_name))
			return (1);
	}
	return (0);
}

t_wc	expand_wildcard(char *pattern)
{
	t_wc			res;
	DIR				*dir;
	struct dirent	*entry;
	char			*clean;

	init_wc(&res, 0);
	clean = strip_pattern(pattern);
	if (!clean)
		return (res.status = 2, res);
	dir = open_wc_dir(&res);
	if (!dir)
		return (free(clean), res);
	entry = readdir(dir);
	while (entry)
	{
		if (handle_entry(&res, entry, clean))
			return (closedir(dir), free_split(res.matches),
				init_wc(&res, 2), res);
		entry = readdir(dir);
	}
	if (res.matches)
		sort_matches(res.matches);
	return (free(clean), closedir(dir), res);
}

static int	process_wildcard(t_cmd *cmd, int *i)
{
	t_wc	wc;
	char	**new_argv;

	wc = expand_wildcard(cmd->argv[*i]);
	if (wc.status == 2)
		return (free_split(wc.matches), 1);
	if (wc.matches)
	{
		new_argv = insert_into_argv(cmd->argv, wc.matches, *i);
		if (!new_argv)
			return (free_split(wc.matches), 1);
		cmd->argv = new_argv;
		*i += ft_arrlen(wc.matches);
		free_split(wc.matches);
		return (2);
	}
	return (0);
}

int	expand_wildcards(t_cmd *cmd)
{
	int	i;
	int	status;
	t_wc	wc;
	t_redir	*r;

	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			if (has_wildcard(cmd->argv[i]))
			{
				status = process_wildcard(cmd, &i);
				if (status == 1)
					return (1);
				if (status == 2)
					continue ;
			}
			remove_quotes_arg(&cmd->argv[i++]);
		}
		r = cmd->redirs;
		while (r)
		{
			if (r->file && has_wildcard(r->file))
			{
				wc = expand_wildcard(r->file);
				if (wc.status == 2)
					return (1);
				// // ❗ bash rule: ambiguous redirect
				// if (!wc.matches || !wc.matches[0] || wc.matches[1])
				// {
				// 	// print_error("minishell", r->file, "ambiguous redirect");
				// 	free_split(wc.matches);
				// 	return (1);
				// }
				free(r->file);
				r->file = ft_strdup(wc.matches[0]);
				free_split(wc.matches);
			}
			if (r->file)
				remove_quotes_arg(&r->file);
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
