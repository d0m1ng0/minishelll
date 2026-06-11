/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:05:41 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/30 21:45:17 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	is_equal(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] == '\0' && b[i] == '\0');
}

int	is_builtin(char *cmd)
{
	if (is_equal(cmd, "echo"))
		return (1);
	if (is_equal(cmd, "cd"))
		return (1);
	if (is_equal(cmd, "pwd"))
		return (1);
	if (is_equal(cmd, "env"))
		return (1);
	if (is_equal(cmd, "exit"))
		return (1);
	if (is_equal(cmd, "export"))
		return (1);
	if (is_equal(cmd, "unset"))
		return (1);
	return (0);
}

int	run_builtin(t_cmd *cmd, t_env **env, t_shell *shell)
{
	int		status;

	status = 0;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_equal(cmd->argv[0], "echo"))
		status = (builtin_echo(cmd->argv));
	else if (is_equal(cmd->argv[0], "pwd"))
		status = (builtin_pwd(shell));
	else if (is_equal(cmd->argv[0], "cd"))
		status = (builtin_cd(cmd->argv, shell));
	else if (is_equal(cmd->argv[0], "env"))
		status = (builtin_env(*env));
	else if (is_equal(cmd->argv[0], "export"))
		status = (builtin_export(env, cmd->argv));
	else if (is_equal(cmd->argv[0], "unset"))
		status = (builtin_unset(env, cmd->argv));
	else if (is_equal(cmd->argv[0], "exit"))
		status = (builtin_exit(cmd->argv, shell));
	return (status);
}

// if (status == -1)
// {
// 	shell->should_exit = 1;
// 	shell->exit_status = 1;
// }
// shell->exit_status = status;

void	print_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
