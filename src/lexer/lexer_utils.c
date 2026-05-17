/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 11:24:34 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 18:17:47 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_isoperator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer)
	{
		free_tokens(lexer->tokens);
		free(lexer);
	}
}
