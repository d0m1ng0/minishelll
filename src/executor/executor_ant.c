/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:10:18 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <signal.h>

// static void	print_broken_pipe(void)
// {
// 	ssize_t	ret;

// 	ret = write(2, "minishell: write error: Broken pipe\n", 36);
// 	(void)ret;
// }

void	wait_pipe_children(t_shell *shell, pid_t last_pid)
{
	pid_t	waited;
	int		status;
	int		last;

	last = 0;
	waited = wait(&status);
	while (waited > 0)
	{
		if (waited == last_pid && WIFEXITED(status))
			last = WEXITSTATUS(status);
		else if (waited == last_pid && WIFSIGNALED(status))
			last = 128 + WTERMSIG(status);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
			(void)!write(2, "minishell: write error: Broken pipe\n", 36);
		waited = wait(&status);
	}
	shell->exit_status = last;
}
// print_broken_pipe();

static void	child_io_setup(int *fds, t_cmd *cmd)
{
	if (fds[0] != -1)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (cmd->next)
	{
		dup2(fds[2], STDOUT_FILENO);
		close(fds[1]);
		close(fds[2]);
	}
}

static pid_t	fork_pipe_cmd(t_cmd *cmd, char **envp,
				t_shell *shell, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
	{
		if (pid < 0)
			shell->exit_status = 1;
		return (pid);
	}
	signal(SIGPIPE, SIG_DFL);
	child_io_setup(fds, cmd);
	if (apply_redirections(cmd))
		exit(1);
	if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
		exit(run_builtin(cmd, &shell->env, shell));
	exec_child(cmd, envp);
	exit(127);
}

static pid_t	run_pipe_loop(t_cmd *cmd, char **envp,
				t_shell *shell, int *prev_fd)
{
	int		fds[5];
	pid_t	last_pid;

	last_pid = -1;
	while (cmd)
	{
		fds[0] = *prev_fd;
		fds[1] = -1;
		fds[2] = -1;
		if (cmd->next && pipe(fds + 3) < 0)
			return (shell->exit_status = 1, last_pid);
		if (cmd->next)
		{
			fds[1] = fds[3];
			fds[2] = fds[4];
		}
		last_pid = fork_pipe_cmd(cmd, envp, shell, fds);
		if (*prev_fd != -1)
			close(*prev_fd);
		if (cmd->next)
			close(fds[4]);
		*prev_fd = fds[1];
		cmd = cmd->next;
	}
	return (last_pid);
}

void	executor(t_cmd *cmd, t_shell *shell)
{
	char	**envp;
	int		prev_fd;

	if (!cmd)
		return ;
	if (!cmd->next)
		return (executor_single(cmd, shell, &shell->env));
	prev_fd = -1;
	envp = env_to_envp(shell->env);
	if (!envp)
		return ;
	wait_pipe_children(shell,
		run_pipe_loop(cmd, envp, shell, &prev_fd));
	free_envp(envp);
}
