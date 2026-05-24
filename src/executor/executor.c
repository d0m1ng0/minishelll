/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:36:08 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/24 20:08:13 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "ft_printf.h"
#include "builtin.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

void	ms_run_external(t_cmd *cmd, char **envp)
{
	int	fd;
	pid_t	pid;
	char	*path;
	
	path = ms_find_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		ft_printf("%s: command not found\n", cmd->argv[0]);
		return ;
	}
	// --- DEBUG MSG-----------------
	ft_printf("#=======================================================\n");
	ft_printf("external command launched\n");
	ft_printf("#=======================================================\n");
	// ------------------------------
	pid = fork();
	if (pid == 0)
	{
		// --- HARDCODED -----------------------
		//execve("/usr/bin/ls", cmd->argv, envp);
		// -------------------------------------
		if (cmd->outfile)
		{
			fd = open(cmd->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);// --- ADD DEBUG: if (... < 0)
			close(fd);
		}
		execve(path, cmd->argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	free(path);
}

void	ms_execute_single_cmd(t_cmd *cmd, char **envp)
{
	int	stdout_saved;
	int	fd_file;

	stdout_saved = -1;
	if (!cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
	{
		stdout_saved = dup(STDOUT_FILENO);
		if (stdout_saved < 0)
			return ;
		if (cmd->outfile)
		{
			fd_file = open(cmd->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd_file < 0)
			{	
				perror("open");
				close(stdout_saved);
				return ;
			}
			dup2(fd_file, STDOUT_FILENO);
			close(fd_file);
		}
		run_builtin(cmd);
		dup2(stdout_saved, STDOUT_FILENO);
		close(stdout_saved);
	}
	else
		ms_run_external(cmd, envp);
}

void	ms_executor(t_cmd *cmd, char **envp)
{
	// --- DEBUG MSG-----------------
	ft_printf("#=======================================================\n");
	ft_printf("executor launched\n");
	ft_printf("#=======================================================\n");
	// ------------------------------
	while (cmd)
	{
		ms_execute_single_cmd(cmd, envp);
		cmd = cmd->next;
	}
}
