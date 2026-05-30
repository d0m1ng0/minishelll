/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 23:11:54 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/30 19:08:33 by dverdini         ###   ########.fr       */
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
#include <readline/readline.h>

//#include <stddef.h>

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned)s1[i] - (unsigned)s2[i]);
}

int	ms_run_heredoc(t_cmd *cmd)
{
	int		fd_pipe[2];

	char	*line;
	if (pipe(fd_pipe) <0)
		return (1);
	ft_printf("DELIMITER=[%s]\n", cmd->heredoc_delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, cmd->heredoc_delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd_pipe[1], line, ft_strlen(line));
		write(fd_pipe[1], "\n", 1);
		free(line);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	return (0);
}

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

void	ms_execute_in_child(t_cmd *cmd, char **envp, t_env **env, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_status = run_builtin(cmd, env, shell);
		exit(shell->exit_status);
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
void	ms_execute_pipe(t_cmd *cmd, char **envp, t_env **env, t_shell *shell)
{
	int	fd_prev;
	int	fd[2];
	pid_t	pid;

	fd_prev = -1;
	while(cmd)
	{
		if (cmd->next && pipe(fd) < 0)
			return ;
		pid = fork();
		if (pid == 0)
		{
			if (fd_prev != -1)
			{
				dup2(fd_prev, STDIN_FILENO);
				close(fd_prev);
			}
			if (cmd->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			ms_execute_in_child(cmd, envp, env, shell);
		}
		if (fd_prev != -1)
			close(fd_prev);
		if (cmd->next)
		{
			close(fd[1]);
			fd_prev = fd[0];
		}
		cmd = cmd->next;

	}
	while (wait(NULL) > 0)
		;
}
/*void	ms_execute_pipe(t_cmd *cmd, char **envp, t_env **env)
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
*/
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
		/* --- HEREDOC -----------------------------------------*/
		if (cmd->heredoc_delimiter)
			ms_run_heredoc(cmd);

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

void	ms_execute_single_cmd(t_cmd *cmd, t_env **env, t_shell *shell)
{
	int	stdout_saved;
	int	fd_file;
	char	**envp;

	stdout_saved = -1;
	ft_printf("ENTER SINGLE\n");
	if (!cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
	{
		ft_printf("ENTER BUILTIN\n");
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
		shell->exit_status = run_builtin(cmd, env, shell);
		//shell->exit_status == -1 exit;memmory error
		//check shell->should_exit if == 1 shouid exit if only one command
		//and it needs to save exit_status to another next command
		dup2(stdout_saved, STDOUT_FILENO);
		close(stdout_saved);
	}
	else
	{
		ft_printf("ENTER EXTERNAL\n");
		envp = env_to_envp(*env);
		if (!envp)
			exit(1);//memmory error
		ms_run_external(cmd, envp);
		free_envp(envp);
	}
}

void	ms_executor(t_cmd *cmd, t_env **env, t_shell *shell)
{
	// --- DEBUG MSG-----------------
//	ft_printf("#=======================================================\n");
//	ft_printf("executor launched\n");
//	ft_printf("#=======================================================\n");
	// ------------------------------
	char	**envp;

	if (!cmd)
		return ;
	if (!env)
		return ;
	if (cmd->next)
	{
		envp = env_to_envp(*env);
		if (!envp)
			return ;
		ms_execute_pipe(cmd, envp, env, shell);
		free_envp(envp);
		return ;
	}
	ms_execute_single_cmd(cmd, env, shell);
/*	while (cmd)
	{
		if (cmd && cmd->next)
			ms_execute_pipe(cmd, envp, env);
		else
			ms_execute_single_cmd(cmd, envp, env);
		ms_execute_single_cmd(cmd, env, shell);
		cmd = cmd->next;
	}
*/
}
