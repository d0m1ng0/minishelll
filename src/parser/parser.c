/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:01:22 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/27 12:08:26 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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
	cmd->heredoc_delimiter = NULL;
	return (cmd);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
				free(tmp->argv[i++]);
			free(tmp->argv);
		}
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->heredoc_delimiter)
			free(tmp->heredoc_delimiter);
		free(tmp);
	}
}

static int	add_token_to_cmd(t_cmd *cmd, t_token *token)
{
	if (token->type == TOKEN_WORD)
		return (add_word_to_cmd(cmd, token->value));
	else if (token->type == TOKEN_REDIR_IN)
		return (handle_redir_in(cmd, token));
	else if (token->type == TOKEN_REDIR_OUT)
		return (handle_redir_out(cmd, token));
	else if (token->type == TOKEN_APPEND)
		return (handle_redir_append(cmd, token));
	else if (token->type == TOKEN_HEREDOC)
		return (handle_heredoc(cmd, token));
	printf("Syntax error: unexpected token type %d\n", token->type);
	return (1);
}

static int	handle_pipe(t_cmd **current, t_token *tokens)
{
	if (!(*current)->argv || !tokens->next || tokens->next->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	(*current)->next = create_cmd();
	if (!(*current)->next)
		return (1);
	*current = (*current)->next;
	return (0);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*current;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	current = cmd;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (handle_pipe(&current, tokens))
				return (free_cmds(cmd), NULL);
		}
		else
		{
			if (add_token_to_cmd(current, tokens))
				return (free_cmds(cmd), NULL);
			if (tokens->type != TOKEN_WORD)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (cmd);
}
