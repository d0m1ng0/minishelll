/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:16:35 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 19:31:54 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "parser.h"

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
}	t_builtin;

int		is_builtin(char *cmd);
int		is_equal(char *a, char *b);
int		builtin_echo(char **argv);
int		builtin_pwd(void);
void	run_builtin(t_cmd *cmd);

#endif