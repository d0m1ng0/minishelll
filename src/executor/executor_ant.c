/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:10:18 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/05 17:36:10 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	wait_pipe_children(t_shell *shell)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
	}
	shell->exit_status = last_status;
}

static void	setup_pipe_io(t_cmd *cmd, int prev_fd, int *fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	exec_pipe_child(t_cmd *cmd, char **envp, t_shell *shell)
{
	char	*path;
	int		status;

	if (is_builtin(cmd->argv[0]))
	{
		status = run_builtin(cmd, &shell->env, shell);
		if (status == -1)
		{
			perror("minishell");
			exit(1);
		}
		exit(status);
	}
	path = ms_find_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		perror("command not found");
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror("execve");
	exit(127);
}

static pid_t	fork_pipe_cmd(t_cmd *cmd, char **envp, t_shell *shell,
								int prev_fd, int *fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		setup_pipe_io(cmd, prev_fd, fd);
		exec_pipe_child(cmd, envp, shell);
		exit(1);
	}
	if (pid < 0)
	{
		perror("fork");
		shell->exit_status = 1;
		return (-1);
	}
	return (pid);
}

static void	execute_pipe(t_cmd *cmd, char **envp, t_shell *shell)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) < 0)
		{
			shell->exit_status = 1;
			perror("pipe");
			return ;
		}
		pid = fork_pipe_cmd(cmd, envp, shell, prev_fd, fd);
		if (pid == -1)
			return ;
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	wait_pipe_children(shell);
}

static void executor_pipe(t_cmd *cmd, t_shell *shell, t_env **env)
{
	char	**envp;

	envp = env_to_envp(*env);
	if (!envp)
	{
		perror("minishell");
		exit(1);
	}
	execute_pipe(cmd, envp, shell);
	free_envp(envp);
}

void	executor(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	if (cmd->next)
		executor_pipe(cmd, shell, &shell->env);
	else
		executor_single(cmd, shell, &shell->env);
}
