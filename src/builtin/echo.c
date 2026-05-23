/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:17:49 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 19:56:31 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argv[i] && is_equal(argv[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else
		perror("pwd");
	return (0);
}

int	builtin_cd(char **argv)
{
	if (!argv[1])
		return (printf("cd: missing path\n"), 1);
	if (chdir(argv[1]) != 0)
		return (perror("cd"), 1);
	return (0);
}
