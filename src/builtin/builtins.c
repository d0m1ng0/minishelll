/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:12:24 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 11:04:37 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_equal(argv[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

int	builtin_pwd(t_shell *shell)
{
	char	*pwd;
	char	buf[1024];

	pwd = get_env_value(shell->env, "PWD");
	if (getcwd(buf, sizeof(buf)))
		ft_printf("%s\n", buf);
	else if (pwd)
		ft_printf("%s\n", pwd);
	else
		return (print_error("pwd", NULL, strerror(errno)), 1);
	return (0);
}

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->exported == 1 && env->key && env->value)
			ft_printf("%s=%s\n", env->key, env->value);
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
