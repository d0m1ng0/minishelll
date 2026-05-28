/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 12:56:07 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"
#include "env.h"
#include "expander.h"
#include "debug.h"
#include "executor.h"

#include "shell.h"

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

int	executor(t_cmd *cmd, t_env **env, t_shell *shell)
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

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp))
		return (env_clear(&shell.env), perror("memory here: "), 1);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		cmd = build_pipeline(line, &shell);
		if (!cmd)
			return (free(line), env_clear(&shell.env), perror("memory: "), 1);
		executor(cmd, &shell.env, &shell);
		free(line);
		free_cmds(cmd);
	}
	env_clear(&shell.env);
	return (0);
}
