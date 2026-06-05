/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_ant.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:53:42 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/05 17:41:34 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	handle_builtin(t_cmd *cmd, t_shell *shell, t_env **env)
{
	int	status;

	status = run_builtin(cmd, env, shell);
	//fflush(stdout);
	if (status == -1)
	{
		perror("minishell");
		exit(1);
	}
	shell->exit_status = status;
	return ;
}

static void	exec_child(t_cmd *cmd, char **envp)
{
	char	*path;

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

static void	handle_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

void	executor_single(t_cmd *cmd, t_shell *shell, t_env **env)
{
	char	**envp;
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
		return (handle_builtin(cmd, shell, env));
	envp = env_to_envp(*env);
	if (!envp)
	{
		shell->error_fatal = 1;
		perror("minishell");
		return ;//exit(1);
	}
	pid = fork();
	if (pid == 0)
		exec_child(cmd, envp);
	waitpid(pid, &status, 0);
	handle_status(shell, status);
	free_envp(envp);
}
