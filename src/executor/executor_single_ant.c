/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_ant.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:53:42 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	open_redirect(t_redir *r)
{
	if (r->type == TOKEN_REDIR_IN)
		return (open(r->file, O_RDONLY));
	if (r->type == TOKEN_REDIR_OUT)
		return (open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == TOKEN_APPEND)
		return (open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == TOKEN_HEREDOC)
			fd = cmd->heredoc_fd;
		else
			fd = open_redirect(r);
		if (fd == -1)
			return (print_error(NULL, r->file, strerror(errno)), 1);
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		if (r->type != TOKEN_HEREDOC)
			close(fd);
		r = r->next;
	}
	return (0);
}

static void	handle_builtin_with_redirs(t_cmd *cmd, t_shell *shell, t_env **env)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(cmd))
	{
		shell->exit_status = 1;
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return ;
	}
	ret = run_builtin(cmd, env, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	shell->exit_status = ret;
}

static void	exec_in_fork(t_cmd *cmd, t_shell *shell, t_env **env)
{
	char	**envp;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (apply_redirections(cmd))
			exit(1);
		envp = env_to_envp(*env);
		if (!envp)
			exit(1);
		exec_child(cmd, envp);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

void	executor_single(t_cmd *cmd, t_shell *shell, t_env **env)
{
	int	sv_in;
	int	sv_out;

	if (!cmd)
		return ;
	if (!cmd->argv || !cmd->argv[0])
	{
		if (!cmd->redirs)
			return ;
		sv_in = dup(STDIN_FILENO);
		sv_out = dup(STDOUT_FILENO);
		if (apply_redirections(cmd))
			shell->exit_status = 1;
		dup2(sv_in, STDIN_FILENO);
		dup2(sv_out, STDOUT_FILENO);
		close(sv_in);
		close(sv_out);
		return ;
	}
	if (is_builtin(cmd->argv[0]))
		return (handle_builtin_with_redirs(cmd, shell, env));
	exec_in_fork(cmd, shell, env);
}
