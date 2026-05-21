/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:05:41 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/21 12:03:11 by anegorov         ###   ########.fr       */
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

int	run_builtin(t_cmd *cmd, t_env **env)
{
	if (is_equal(cmd->argv[0], "echo"))
		return (builtin_echo(cmd->argv));
	else if (is_equal(cmd->argv[0], "pwd"))
		return (builtin_pwd());
	else if (is_equal(cmd->argv[0], "cd"))
		return (builtin_cd(cmd->argv));
	else if (is_equal(cmd->argv[0], "env"))
		return (builtin_env(*env));
	else if (is_equal(cmd->argv[0], "export"))
		return (builtin_export(env, cmd->argv));
	else if (is_equal(cmd->argv[0], "unset"))
		return (builtin_unset(env, cmd->argv));
	return (0);
}
