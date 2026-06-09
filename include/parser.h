/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:00:54 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 15:01:51 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token_utils.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir 	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir         *redirs;
	char			*infile;
	char			*outfile;
	int				append;
	char			*heredoc_delimiter;
	int				heredoc_fd; 
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parser(t_token *tokens);
void	free_cmds(t_cmd *cmd);
int		add_word_to_cmd(t_cmd *cmd, char *word);
int		handle_redir_in(t_cmd *cmd, t_token *token);
int		handle_redir_out(t_cmd *cmd, t_token *token);
int		handle_redir_append(t_cmd *cmd, t_token *token);
int		handle_heredoc(t_cmd *cmd, t_token *token);
int		add_redir(t_cmd *cmd, char *file, int type);
int		add_redir_from_token(t_cmd *cmd, t_token *token);

#endif