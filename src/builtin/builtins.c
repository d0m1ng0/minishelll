/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:12:24 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/03 13:06:17 by anegorov         ###   ########.fr       */
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
		if (argv[i + 1] && argv[i + 1][0] != '\0')
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(t_shell *shell)
{
	char	*pwd;
	char	buf[1024];

	pwd = get_env_value(shell->env, "PWD");
	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else if (pwd)
		printf("%s\n", pwd);
	else
		return (print_error("pwd", NULL, strerror(errno)), 1);
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*oldpwd;
	char	*newpwd;
	char	*home;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (print_error("cd", NULL, strerror(errno)), 1);
	if (!argv[1])
	{
		home = get_env_value(shell->env, "HOME");
		if (!home)
			return (print_error("cd", NULL, "HOME not set"), 1);
		if (chdir(home) != 0)
			return (free(oldpwd), print_error("cd", home, strerror(errno)), 1);
	}
	else if (chdir(argv[1]) != 0)
		return (free(oldpwd), print_error("cd", argv[1], strerror(errno)), 1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (free(oldpwd), print_error("cd", NULL, strerror(errno)), 1);
	if (set_env_value(&shell->env, "OLDPWD", oldpwd))
		return (free(oldpwd), free(newpwd), 1);
	if (set_env_value(&shell->env, "PWD", newpwd))
		return (free(oldpwd), free(newpwd), 1);
	return (free(oldpwd), free(newpwd), 0);
}

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->exported == 1 && env->key && env->value)
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
