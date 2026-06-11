/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:59:32 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/30 18:13:33 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H 
# define SIGNALS_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <unistd.h>

void	ms_handle_sigint(int sig);
void	ms_signals_setup(void);

#endif
