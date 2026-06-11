/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:25:52 by dverdini          #+#    #+#             */
/*   Updated: 2026/06/11 19:36:19 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "libft.h"

char	*ms_get_path_value(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*ms_create_path_candidate(char *dir, char *cmd)
{
	char	*tmp;
	char	*path_candidate;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (tmp == NULL)
		return (NULL);
	path_candidate = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path_candidate);
}

static char	*ms_find_in_dirs(char **dirs, char *cmd)
{
	int		i;
	char	*dir_candidate;

	i = 0;
	while (dirs[i])
	{
		dir_candidate = ms_create_path_candidate(dirs[i], cmd);
		if (dir_candidate && access(dir_candidate, X_OK) == 0)
		{
			free_split(dirs);
			return (dir_candidate);
		}
		free(dir_candidate);
		i++;
	}
	free_split(dirs);
	return (NULL);
}

char	*ms_find_cmd_path(char *cmd, char **envp)
{
	char	*path_to_search;
	char	**dirs;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_to_search = ms_get_path_value(envp);
	if (!path_to_search)
		return (NULL);
	dirs = ft_split(path_to_search, ':');
	if (!dirs)
		return (NULL);
	return (ms_find_in_dirs(dirs, cmd));
}
