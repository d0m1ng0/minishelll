/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:36:08 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/24 12:43:52 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "ft_printf.h"
#include "builtin.h"
#include <unistd.h>
#include <sys/wait.h>

void	ms_run_external(t_cmd *cmd, char **envp)
{
	(void)cmd;
	(void)envp;
	pid_t	pid;

	// --- DEBUG MSG-----------------
	ft_printf("#=======================================================\n");
	ft_printf("external command launched\n");
	ft_printf("#=======================================================\n");
	// ------------------------------
	pid = fork();
	if (pid == 0)
		execve("/usr/bin/ls", cmd->argv, envp);
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
