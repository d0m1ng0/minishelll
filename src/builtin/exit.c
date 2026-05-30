/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:33:49 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 10:46:45 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	long long	code;

	printf("exit\n");
	if (!argv[1])
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (!is_numeric(argv[1]))
	{
		print_error("exit", argv[1], "numeric argument required");
		return (2);
	}
	if (argv[2])
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	shell->should_exit = 1;
	code = ft_atoll(argv[1]);
	return ((unsigned char)code);
}
