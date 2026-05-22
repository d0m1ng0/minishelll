/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/22 15:00:14 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"
#include "env.h"
#include "expander.h"

t_cmd	*build_cmds(char *line);

// void execute_cmd(t_cmd *cmd)
// {
// 	getenv("PATH");
// }


int	execute_single_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv[0]))
		return (run_builtin(cmd, env));
	// else
	// 	run_external(cmd);
	return (0);
}

int	executor(t_cmd *cmd, t_env **env)
{
	while (cmd)
	{
		if (execute_single_cmd(cmd, env))
			return (1);//error memmory
		cmd = cmd->next;
	}
	return (0);
}

void	print_cmd(t_cmd *cmd)
{
	size_t	i;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->argv && tmp->argv[i])
		{
			printf("ARGV[%zu]: %s file: %s output: %s\n", i,
				tmp->argv[i], tmp->infile, tmp->outfile);
			i++;
		}
		tmp = tmp->next;
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->exported == 1)
			printf("Key = %s Value = %s\n", env->key, env->value);
		env = env->next;
	}
}

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
}	t_shell;

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env	*env;
	t_shell	shell;

	(void)argc;
	(void)argv;
	env_init(&env, envp);
	if (!env)
		return (printf("memory error\n"), 1);
	// print_env(env);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		cmd = build_cmds(line);
		if (!cmd)
			return (free(line), env_clear(&env), printf("memory error\n"), 1);
		//print_cmd(cmd);
		shell.env = env;
		shell.exit_status = 0;
		expand_var(cmd, &shell);
		// expand(*, $var);execute();free everything
		executor(cmd, &env);
		free(line);
		free_cmds(cmd);
	}
	env_clear(&env);
	return (0);
}
