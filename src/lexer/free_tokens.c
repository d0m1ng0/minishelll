/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:07:44 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:08:12 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_tokens(t_token *tokens)
{
	t_token	*tmp_next;

	while (tokens)
	{
		tmp_next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp_next;
	}
}
