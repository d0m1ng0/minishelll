/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:15:55 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 19:44:57 by anegorov         ###   ########.fr       */
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

void	run_builtin(t_cmd *cmd)
{
	if (is_equal(cmd->argv[0], "echo"))
		builtin_echo(cmd->argv);
	else if (is_equal(cmd->argv[0], "pwd"))
		builtin_pwd();
	else if (is_equal(cmd->argv[0], "cd"))
		builtin_cd(cmd->argv);
}
