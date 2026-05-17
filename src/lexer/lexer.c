/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 11:24:39 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 18:17:52 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	tokenize(t_lexer *lexer)
{
	while (lexer->input[lexer->pos] != '\0')
	{
		if (ft_isspace(lexer->input[lexer->pos]))
			lexer->pos++;
		else if (ft_isoperator(lexer->input[lexer->pos]))
		{
			if (handle_operator(lexer) == 1)
				return (1);
		}
		else
		{
			if (handle_word(lexer) == 1)
				return (1);
		}
	}
	return (0);
}

t_lexer	*lexer_init(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	lexer->tokens = NULL;
	return (lexer);
}
