/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:36:08 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/24 18:21:35 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "ft_printf.h"
#include "builtin.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void	ms_run_external(t_cmd *cmd, char **envp)
{
	(void)cmd;
	(void)envp;
	int	fd;
	pid_t	pid;
	char	*path;
	
	path = ms_find_cmd_path(cmd->argv[0], envp);
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
				return ;
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		execve(path, cmd->argv, envp);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

void	ms_execute_single_cmd(t_cmd *cmd, char **envp)
{
	if (!cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
		run_builtin(cmd);
	else
		ms_run_external(cmd, envp);
}

void	ms_executor(t_cmd *cmd, char **envp)
{
	(void)envp;

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
