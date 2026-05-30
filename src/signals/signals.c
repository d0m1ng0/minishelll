/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 17:56:17 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/30 18:14:35 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/*
SIGINT reçu
- newline
- readline reset
- nouveau prompt
*/
//signal(SIGINT, ms_handle_sigint); //arriva il segnale
void	ms_handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ms_signals_setup(void)
{
	signal(SIGINT, ms_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
