/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:47:36 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:16:13 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
#include <.h>
#include ".h"

main

inizializzo la shell
[]while infinito:
[ok]	leggo una linea mostrando il prompt con readline
	
[ok]	se readline ritorna NULL:
	    esco dalla shell
	
[ok]	se la linea non è vuota:
	    aggiungo alla history
	
[]	passo la linea al lexer/parser
	
[]	eseguo il risultato
	
[]	libero la linea e le strutture temporanee

fine programma
*/

//#include "minishell.h"


int	main(void)//int argc, char **argv)
{
	t_token	*tokens;

	char	*line;

	tokens = NULL;
	while (1)
	{
		line = ms_read_line();
		if (ms_handle_EOF(line))
			break ;
		ms_add_history(line);
		tokens = ms_lexer(line);
		ms_print_tokens(tokens);
		ms_free_tokens(tokens);
		//ms_debug_print_line(line);
		ms_cleanup_line(line);
	}
	return (0);
}
/*DEPRECATED - MINISHELL PROJECT IS UNDERCONSTRUCTION
 * void	ms_debug_print_line(char *line)
{
	if (!line)
		return ;
	ft_printf("%s\n", line);
}
*/

