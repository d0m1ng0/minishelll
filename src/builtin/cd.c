/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:12:24 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 11:04:37 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	update_pwd(t_shell *shell, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (free(oldpwd),
			print_error("cd", NULL, strerror(errno)), 1);
	if (set_env_value(&shell->env, "OLDPWD", oldpwd)
		|| set_env_value(&shell->env, "PWD", newpwd))
		return (free(newpwd), 1);
	free(newpwd);
	return (0);
}

static int	cd_home(t_shell *shell, char *oldpwd)
{
	char	*home;

	home = get_env_value(shell->env, "HOME");
	if (!home)
		return (free(oldpwd),
			print_error("cd", NULL, "HOME not set"), 1);
	if (chdir(home) != 0)
		return (free(oldpwd),
			print_error("cd", home, strerror(errno)), 1);
	return (0);
}

// int	builtin_cd(char **argv, t_shell *shell)
// {
//   char	*oldpwd;
//   char	*newpwd;
//   char	*home;

//   oldpwd = getcwd(NULL, 0);
//   if (!oldpwd)
//     return (print_error("cd", NULL, strerror(errno)), 1);
//   if (!argv[1])
//   {
//     home = get_env_value(shell->env, "HOME");
//     if (!home)
//       return (print_error("cd", NULL, "HOME not set"), 1);
//     if (chdir(home) != 0)
//       return (free(oldpwd), print_error("cd", home, strerror(errno)), 1);
//   }
//   else if (chdir(argv[1]) != 0 && !argv[2])
//     return (free(oldpwd), print_error("cd", argv[1], strerror(errno)), 1);
//   else if (argv[2])
//     return (free(oldpwd), print_error("cd", NULL, "too many arguments"), 1);
//   newpwd = getcwd(NULL, 0);
//   if (!newpwd)
//     return (free(oldpwd), print_error("cd", NULL, strerror(errno)), 1);
//   if (set_env_value(&shell->env, "OLDPWD", oldpwd)
//     || set_env_value(&shell->env, "PWD", newpwd))
//     return (free(oldpwd), free(newpwd), 1);
//   return (free(oldpwd), free(newpwd), 0);
// }

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (print_error("cd", NULL, strerror(errno)), 1);
	if (!argv[1])
	{
		if (cd_home(shell, oldpwd))
			return (1);
	}
	else if (argv[2])
		return (free(oldpwd),
			print_error("cd", NULL, "too many arguments"), 1);
	else if (chdir(argv[1]) != 0)
		return (free(oldpwd),
			print_error("cd", argv[1], strerror(errno)), 1);
	if (update_pwd(shell, oldpwd))
		return (1);
	free(oldpwd);
	return (0);
}
