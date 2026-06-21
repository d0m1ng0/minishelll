/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 18:50:40 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/21 15:20:39 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

t_cmd	*build_cmds(char *line)
{
	t_lexer	*lexer;
	t_cmd	*cmd;
	int		tokenize_result;

	lexer = lexer_init(line);
	if (!lexer)
		return (NULL);
	tokenize_result = tokenize(lexer);
	if (tokenize_result)
	{
		free_lexer(lexer);
		return (NULL);
	}
	cmd = parser(lexer->tokens);
	free_lexer(lexer);
	if (!cmd)
	{
		return (NULL);
	}
	return (cmd);
}
