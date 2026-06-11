/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:01:22 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 15:38:03 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
}

// if (tmp->infile)
// 	free(tmp->infile);
// if (tmp->outfile)
// 	free(tmp->outfile);

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
		if (tmp->heredoc_delimiter)
			free(tmp->heredoc_delimiter);
		if (tmp->redirs)
			free_redirs(tmp->redirs);
		free(tmp);
	}
}

// static int	add_token_to_cmd(t_cmd *cmd, t_token *token)
// {
// 	if (token->type == TOKEN_WORD)
// 		return (add_word_to_cmd(cmd, token->value));
// 	// else if (token->type == TOKEN_REDIR_IN)
// 	// 	return (handle_redir_in(cmd, token));
// 	// else if (token->type == TOKEN_REDIR_OUT)
// 	// 	return (handle_redir_out(cmd, token));
// 	// else if (token->type == TOKEN_APPEND)
// 	// 	return (handle_redir_append(cmd, token));
// 	// else if (token->type == TOKEN_HEREDOC)
// 	// 	return (handle_heredoc(cmd, token));
// 	else
// 		return (add_redir_from_token(cmd, token));
// 	// ft_putstr_fd("Syntax error: unexpected token type\n", 2);
// 	return (1);
// }
//void	print_error(char *cmd, char *arg, char *msg)

int	add_token_to_cmd(t_cmd *cmd, t_token *token)
{
	if (token->type == TOKEN_WORD)
		return (add_word_to_cmd(cmd, token->value));
	return (handle_redir(cmd, token));
}

//if (!(*current)->argv || !tokens->next || tokens->next->type == TOKEN_PIPE)

static int	handle_pipe(t_cmd **current, t_token *tokens)
{
	if ((!(*current)->argv && !(*current)->redirs)
		|| !tokens->next
		|| tokens->next->type == TOKEN_PIPE)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	(*current)->next = create_cmd();
	if (!(*current)->next)
		return (1);
	*current = (*current)->next;
	return (0);
}

// while (tokens)
// {
// 	if (tokens->type == TOKEN_PIPE)
// 	{
// 		if (handle_pipe(&current, tokens))
// 			return (free_cmds(cmd), NULL);
// 	}
// 	else
// 	{
// 		if (add_token_to_cmd(current, tokens))
// 			return (free_cmds(cmd), NULL);
// 		if (tokens->type != TOKEN_WORD)
// 			tokens = tokens->next;
// 	}
// 	tokens = tokens->next;
// }

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
		if (tokens->type == TOKEN_PIPE && handle_pipe(&current, tokens))
			return (free_cmds(cmd), NULL);
		else if (tokens->type == TOKEN_WORD
			&& add_word_to_cmd(current, tokens->value))
			return (free_cmds(cmd), NULL);
		else if (tokens->type != TOKEN_WORD && tokens->type != TOKEN_PIPE)
		{
			if (handle_redir(current, tokens))
				return (free_cmds(cmd), NULL);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (cmd);
}
