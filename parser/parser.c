/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:01:22 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/16 18:40:15 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

static void	add_word_to_cmd(t_cmd *cmd, char *word)
{
	size_t	i;
	char	**new_argv;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
		// destroy_all_exit(cmd);
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = word;
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	add_token_to_cmd(t_cmd *cmd, t_token *token)
{
	if (token->type == TOKEN_WORD)
	{
		add_word_to_cmd(cmd, token->value);
	}
	else if (token->type == TOKEN_REDIR_IN)
	{
		// Set cmd->infile to the next token's value
	}
	else if (token->type == TOKEN_REDIR_OUT)
	{
		// Set cmd->outfile to the next token's value and cmd->append to 0
	}
	else if (token->type == TOKEN_APPEND)
	{
		// Set cmd->outfile to the next token's value and cmd->append to 1
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		// Handle heredoc logic
	}
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*current_cmd;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);//destroy_exit()
	current_cmd = cmd;
	while (tokens)
	{
		// if (tokens->type == TOKEN_PIPE)
		// {
		// 	current_cmd->next = create_cmd();
		// 	if (!current_cmd->next)
		// 		return (NULL);//destroy_exit()
		// 	current_cmd = current_cmd->next;
		// }
		// else
		add_token_to_cmd(current_cmd, tokens);
		tokens = tokens->next;
	}
	return (cmd);
}
