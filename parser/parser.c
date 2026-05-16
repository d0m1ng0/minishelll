/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:01:22 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/16 16:49:35 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*current_cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	current_cmd = cmd;
	while (tokens)
	{
		current_cmd->argv = NULL;
		current_cmd->infile = NULL;
		current_cmd->outfile = NULL;
		current_cmd->append = 0;
		current_cmd->next = NULL;
		if (!cmd)
			cmd = current_cmd;
		else
			cmd->next = current_cmd;
		tokens = tokens->next;
	}
	return (cmd);
}
