/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:37:01 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 18:18:05 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	add_word_to_cmd(t_cmd *cmd, char *word)
{
	size_t	i;
	char	**new_argv;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return (1);
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(word);
	if (!new_argv[i])
		return (free(new_argv), 1);
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (0);
}

int	handle_redir_in(t_cmd *cmd, t_token *token)
{
	token = token->next;
	if (!token)
		return (printf("syntax error near unexpected token `newline'\n"), 1);
	else if (token->type != TOKEN_WORD)
		return (printf("syntax error near unexpected token `>'\n"), 1);
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup(token->value);
	if (!cmd->infile)
		return (1);
	cmd->append = 0;
	return (0);
}

int	handle_redir_out(t_cmd *cmd, t_token *token)
{
	token = token->next;
	if (!token)
		return (printf("syntax error near unexpected token `newline'\n"), 1);
	else if (token->type != TOKEN_WORD)
		return (printf("syntax error near unexpected token `>'\n"), 1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(token->value);
	if (!cmd->outfile)
		return (1);
	cmd->append = 0;
	return (0);
}

int	handle_heredoc(t_cmd *cmd, t_token *token)
{
	token = token->next;
	if (!token)
		return (printf("syntax error near unexpected token `newline'\n"), 1);
	if (token->type != TOKEN_WORD)
		return (printf("syntax error near unexpected token `<<'\n"), 1);
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	cmd->heredoc_delimiter = ft_strdup(token->value);
	if (!cmd->heredoc_delimiter)
		return (1);
	return (0);
}

int	handle_redir_append(t_cmd *cmd, t_token *token)
{
	token = token->next;
	if (!token)
		return (printf("syntax error near unexpected token `newline'\n"), 1);
	else if (token->type != TOKEN_WORD)
		return (printf("syntax error near unexpected token `>>'\n"), 1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(token->value);
	cmd->append = 1;
	if (!cmd->outfile)
		return (1);
	return (0);
}
