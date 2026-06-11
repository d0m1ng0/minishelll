/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <signal.h>

static void	exec_error(char *cmd, char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	exit(code);
}

void	exec_child(t_cmd *cmd, char **envp)
{
	char		*path;
	struct stat	st;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(0);
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (access(cmd->argv[0], F_OK) != 0)
			exec_error(cmd->argv[0], ": No such file or directory\n", 127);
		if (stat(cmd->argv[0], &st) == 0 && S_ISDIR(st.st_mode))
			exec_error(cmd->argv[0], ": Is a directory\n", 126);
		signal(SIGPIPE, SIG_DFL);
		execve(cmd->argv[0], cmd->argv, envp);
		exec_error(cmd->argv[0], ": Permission denied\n", 126);
	}
	path = ms_find_cmd_path(cmd->argv[0], envp);
	if (!path)
		exec_error(cmd->argv[0], ": command not found\n", 127);
	signal(SIGPIPE, SIG_DFL);
	execve(path, cmd->argv, envp);
	free(path);
	exit(127);
}
