/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_ant.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:53:42 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 16:38:05 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	handle_builtin(t_cmd *cmd, t_shell *shell, t_env **env)
{
	int	status;

	status = run_builtin(cmd, env, shell);
	if (status == -1)
	{
		shell->exit_status = 1;
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

void	handle_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

int apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		fd = -1;
		// printf("file: %s type(%d)\n", r->file, r->type);
		if (r->type == TOKEN_REDIR_IN)
			fd = open(r->file, O_RDONLY);
		else if (r->type == TOKEN_REDIR_OUT)
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == TOKEN_APPEND)
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// else if (r->type == TOKEN_HEREDOC)
		//     fd = ms_run_heredoc(r);
		if (fd == -1)
		{
			print_error(NULL, r->file, strerror(errno));
			return (1);
		}
		else
		{
			if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		r = r->next;
	}
	return (0);
}

void executor_single(t_cmd *cmd, t_shell *shell, t_env **env)
{
    char **envp;
    pid_t pid;
    int status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return;
	pid = fork();
	if (pid == 0)
	{
		if(apply_redirections(cmd) == 1)
		{
			// shell->exit_status = 1;
			exit(1) ;
		}
		if (is_builtin(cmd->argv[0]))
		{
			shell->exit_status = run_builtin(cmd, env, shell);
			exit(shell->exit_status);
		}
		envp = env_to_envp(*env);
		if (!envp)
			exit(1);
		exec_child(cmd, envp);
	}
	waitpid(pid, &status, 0);
	handle_status(shell, status);
}

// void	executor_single(t_cmd *cmd, t_shell *shell, t_env **env)
// {
// 	char	**envp;
// 	pid_t	pid;
// 	int		status;

// 	if (!cmd || !cmd->argv || !cmd->argv[0])
// 		return ;
// 	if (is_builtin(cmd->argv[0]))
// 		return (handle_builtin(cmd, shell, env));
// 	envp = env_to_envp(*env);
// 	if (!envp)
// 	{
// 		shell->error_fatal = 1;
// 		perror("minishell");
// 		return ;//exit(1);
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 		exec_child(cmd, envp);
// 	waitpid(pid, &status, 0);
// 	handle_status(shell, status);
// 	free_envp(envp);
// }