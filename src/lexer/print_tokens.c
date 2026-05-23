/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:08:40 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:08:52 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TYPE_WORD)
			ft_printf("[WORD] %s\n", tokens->value);
		if (tokens->type == TYPE_PIPE)
			ft_printf("[PIPE] %s\n", tokens->value);
		tokens = tokens->next;
	}
}
