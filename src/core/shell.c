/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:57:07 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 10:47:10 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_shell(t_shell *shell, char **envp)
{
	t_env	*env;

	if (!shell)
		return (0);
	shell->env = NULL;
	env_init(&env, envp);
	if (!env)
		return (1);
	shell->env = env;
	shell->exit_status = 0;
	shell->should_exit = 0;
	return (0);
}
