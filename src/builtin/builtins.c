/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:12:24 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/27 15:49:24 by anegorov         ###   ########.fr       */
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
		return (print_error("pwd", NULL, strerror(errno)), 1);
	return (0);
}

int	builtin_cd(char **argv)
{
	if (!argv[1])
		return (print_error("cd", NULL, "missing path"), 1);
	if (chdir(argv[1]) != 0)
		return (print_error("cd", argv[1], strerror(errno)), 1);
	return (0);
}

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->exported == 1)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	builtin_unset(t_env **env, char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		remove_env_var(env, argv[i]);
		i++;
	}
	return (0);
}
