/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:36:08 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/29 12:08:34 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "ft_printf.h"
#include "builtin.h"
#include "env.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

/*
pms_execute_pipe()
{
	creo pipe fd[2]

	fork primo child:
		dup2(fd[1], STDOUT_FILENO)
		close fd[0]
		close fd[1]
		eseguo cmd1

	fork second child:
		dup2(fd[0], STDIN_FILENO)
		close fd[0]
		close fd[1]
		eseguo cmd2

	parent:
		closefd[0]
		close fd[1]
		waitpid child1
		waitpid child2		
}
*/

void	ms_execute_in_child(t_cmd *cmd, char **envp, t_env **env)
{
	char	*path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd->argv[0]))
	{
		run_builtin(cmd, env);
		exit(EXIT_SUCCESS);
	}
	path = ms_find_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		ft_printf("%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	exit(EXIT_FAILURE);
}

void	ms_execute_pipe(t_cmd *cmd, char **envp, t_env **env)
{
	int	fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) < 0)
		return ;
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		//ft_printf("child1\n");
		//ms_execute_single_cmd(cmd, envp, env);
		ms_execute_in_child(cmd, envp, env);
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		//ft_printf("child2\n");
		//ms_execute_single_cmd(cmd->next, envp, env);
		ms_execute_in_child(cmd->next, envp, env);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

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
//	// --- DEBUG MSG-----------------
//	ft_printf("#=======================================================\n");
//	ft_printf("external command launched\n");
//	ft_printf("#=======================================================\n");
//	// ------------------------------
	pid = fork();
	if (pid == 0)
	{
		// --- HARDCODED -----------------------
		//execve("/usr/bin/ls", cmd->argv, envp);
		// -------------------------------------
		if (cmd->outfile)
		{

			if (cmd->append)
				fd = open(cmd->outfile,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
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
		if (cmd->infile)
		{
			fd = open(cmd->infile, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				perror("dup2");
				close(fd);
				exit(EXIT_FAILURE);
			}
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

void	ms_execute_single_cmd(t_cmd *cmd, char **envp, t_env **env)
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
			if (cmd->append)
				fd_file = open(cmd->outfile,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
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
		run_builtin(cmd, env);
		dup2(stdout_saved, STDOUT_FILENO);
		close(stdout_saved);
	}
	else
		ms_run_external(cmd, envp);
}

void	ms_executor(t_cmd *cmd, char **envp, t_env **env)
{
	// --- DEBUG MSG-----------------
//	ft_printf("#=======================================================\n");
//	ft_printf("executor launched\n");
//	ft_printf("#=======================================================\n");
	// ------------------------------
	if (!cmd)
		return ;
	if (cmd->next)
	{
		ms_execute_pipe(cmd, envp, env);
		return ;
	}
	ms_execute_single_cmd(cmd, envp, env);
/*	while (cmd)
	{
		if (cmd && cmd->next)
			ms_execute_pipe(cmd, envp, env);
		else
			ms_execute_single_cmd(cmd, envp, env);
		cmd = cmd->next;
	}
*/
}
