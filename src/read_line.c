/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:55:59 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/22 12:14:15 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_read_line(void)
{
	char	*line;

	line = readline("minihell$ ");
	return (line);
}

/*
LESSON
char *readline(const char *prompt);
readline prende una stringa prompt e ritorna un char *

DESCRIPTION
       readline  will read a line from the terminal and return it, using prompt as a prompt.  If prompt is NULL
       or the empty string, no prompt is issued.  The line returned is allocated  with  malloc(3);  the  caller
       must  free  it  when finished.  The line returned has the final newline removed, so only the text of the
       line remains.

       readline offers editing capabilities while the user is entering the line.  By default, the line  editing
       commands are similar to those of emacs.  A vi-style line editing interface is also available.

       This  manual  page describes only the most basic use of readline.  Much more functionality is available;
       see The GNU Readline Library and The GNU History Library for additional information.

RETURN VALUE
       readline returns the text of the line read.  A blank line returns the empty string.  If EOF  is  encoun‐
       tered while reading a line, and the line is empty, NULL is returned.  If an EOF is read with a non-empty
       line, it is treated as a newline.

*/
