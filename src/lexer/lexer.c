/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:09:05 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:11:48 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ms_lexer(char *line)
{
	t_token	*tokens;
	char	*word;
	int		i;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (ms_is_space(line[i]))
			i++;
		else if (line[i] == '|')
		{
			ms_add_token_back(&tokens, ms_create_token(TYPE_PIPE, ft_strdup("|")));
			i++;
		}
		else
		{
			word = ms_read_word(line, &i);
			ms_add_token_back(&tokens, ms_create_token(TYPE_WORD, word));
		}
	}
	return (tokens);
}
