/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/05/30 22:23:49 by anegorov         ###   ########.fr       */
=======
/*   Updated: 2026/05/30 18:17:30 by dverdini         ###   ########.fr       */
>>>>>>> origin/feature/executor
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"
#include "env.h"
#include "expander.h"
#include "executor.h"
#include "shell.h"
#include "get_next_line.h"
#include "debug.h"
#include "signals.h"

// void	print_cmd(t_cmd *cmd)
// {
// 	size_t	i;
// 	t_cmd	*tmp;

// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		printf("----- CMD -----\n");
// 		i = 0;
// 		while (tmp->argv && tmp->argv[i])
// 		{
// 			printf("ARGV[%zu]: %s\n", i, tmp->argv[i]);
// 			i++;
// 		}
// 		printf("INFILE: %s\n", tmp->infile ? tmp->infile : "NULL");
// 		printf("OUTFILE: %s\n", tmp->outfile ? tmp->outfile : "NULL");
// 		tmp = tmp->next;
// 	}
// }

// void	print_env(t_env *env)
// {
// 	while (env)
// 	{
// 		if (env->exported == 1)
// 			printf("Key = %s Value = %s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd	*cmd;
// 	char	*line;
// 	t_shell	shell;

// 	(void)argc;
// 	(void)argv;
// 	if (init_shell(&shell, envp))
// 		return (env_clear(&shell.env), perror("memory here: "), 1);
// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line)
// 			break ;
// 		cmd = build_pipeline(line, &shell);
// 		if (!cmd)
// 			return (free(line), env_clear(&shell.env), perror("memory: "), 1);
// 		ms_executor(cmd, &shell.env, &shell);
// 		free(line);
// 		free_cmds(cmd);
// 	}
// 	env_clear(&shell.env);
// 	return (0);
// }

int	execute_single_cmd(t_cmd *cmd, t_env **env, t_shell *shell)
{
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv[0]))
		return (run_builtin(cmd, env, shell));
	return (0);
}
// else
	// 	run_external(cmd);

/* --- ANTONINA - EXECUTOR ----------------------------------------------*/
/*int	executor(t_cmd *cmd, t_env **env, t_shell *shell)
{
	int	status;

	while (cmd)
	{
		status = execute_single_cmd(cmd, env, shell);
		if (status == -1)
		{
			perror("minishell");
			exit(1);
		}
		shell->exit_status = status;
		cmd = cmd->next;
		if (shell->should_exit)
			exit(shell->exit_status);
	}
	return (0);
}
*/
/* --- ANTONINA - GNL ---------------------------------------------------*/

char	*get_line(void)
{
	char	*line;
	size_t	len;

	if (isatty(STDIN_FILENO))
		line = readline("minishell> ");
	else
		line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

// char	*get_line(void)
// {
// 	return (readline("minish-1.0$ "));
// }

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp))
		return (env_clear(&shell.env), perror("memory here: "), 1);
	ms_signals_setup();
	while (1)
	{
		line = get_line();
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		cmd = build_pipeline(line, &shell);
		if (!cmd)
			return (free(line), env_clear(&shell.env), perror("memory: "), 1);
		ms_executor(cmd, &shell.env, &shell);
		free(line);
		free_cmds(cmd);
	}
	env_clear(&shell.env);
	return (shell.exit_status);
}
