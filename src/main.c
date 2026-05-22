/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:47:36 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/22 12:06:57 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
#include <.h>
#include ".h"

main

inizializzo la shell
while infinito:
    leggo una linea mostrando il prompt con readline

    se readline ritorna NULL:
        esco dalla shell

    se la linea non è vuota:
        aggiungo alla history

    passo la linea al lexer/parser

    eseguo il risultato

    libero la linea e le strutture temporanee

fine programma
*/

int	main(void)//int argc, char **argv)
{
	char	*line;
	while (1)
	{
		
		line = ms_read_line();
		if (line == NULL) //receive ctrl+D
			break ;
		free(line);
	}
	return (0);
}
