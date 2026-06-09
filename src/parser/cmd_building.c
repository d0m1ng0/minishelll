/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:37:01 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 16:07:48 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// static void	print_error(char *cmd, char *arg, char *msg)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	if (cmd)
// 	{
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": ", 2);
// 	}
// 	if (arg)
// 	{
// 		ft_putstr_fd("'", 2);
// 		ft_putstr_fd(arg, 2);
// 		ft_putstr_fd("': ", 2);
// 	}
// 	ft_putstr_fd(msg, 2);
// 	ft_putstr_fd("\n", 2);
// }

int	add_redir(t_cmd *cmd, char *file, int type)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (1);
	new->file = ft_strdup(file);
	if (!new->file)
		return (free(new), 1);
	new->type = type;
	new->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

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
	// int fd;

	token = token->next;
	if (!token)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	else if (token->type != TOKEN_WORD)
		return (ft_putstr_fd("syntax error near unexpected token `>'\n", 2), 1);
	// fd = open(token->value, O_RDONLY);
	// if (fd == -1)
	// 	return (print_error(NULL, token->value, strerror(errno)), 1);
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
	// int fd;

	token = token->next;
	if (!token)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	else if (token->type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
		return (1);
	}
	// fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (fd == -1)
	// 	return (print_error(NULL, token->value, strerror(errno)), 1);
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
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (token->type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
		return (1);
	}
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	cmd->heredoc_delimiter = ft_strdup(token->value);
	if (!cmd->heredoc_delimiter)
		return (1);
	return (0);
}

int	handle_redir_append(t_cmd *cmd, t_token *token)
{
	// int fd;

	token = token->next;
	if (!token)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	else if (token->type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (-1);
	}
	// fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// if (fd == -1)
	// 	return (print_error(NULL, token->value, strerror(errno)), -1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(token->value);
	cmd->append = 1;
	if (!cmd->outfile)
		return (1);
	return (0);
}

int	add_redir_from_token(t_cmd *cmd, t_token *token)
{
	t_token_type	op;

	op = token->type;
	token = token->next;
	if (!token || token->type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error\n", 2);
		return (1);
	}

	return add_redir(cmd, token->value, op);
}
