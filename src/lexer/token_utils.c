/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:11:05 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:11:56 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ms_create_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	ms_add_token_back(t_token **tokens, t_token *new)
{
	t_token	*token_last;

	if (!tokens || !new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	token_last = *tokens;
	while (token_last->next)
		token_last = token_last->next;
	token_last->next = new;
}

