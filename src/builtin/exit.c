/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +:+           */
/*   Created: 2026/05/28 09:33:49 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
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

static int	is_out_of_range(const char *num, int sign)
{
	const char	*limit;
	size_t		len;
	size_t		lim_len;

	if (sign < 0)
		limit = "9223372036854775808";
	else
		limit = "9223372036854775807";
	len = ft_strlen(num);
	lim_len = ft_strlen(limit);
	if (len > lim_len)
		return (1);
	if (len < lim_len)
		return (0);
	return (ft_strncmp(num, limit, lim_len) > 0);
}

static long long	ft_atoll_safe(const char *str, int *overflow)
{
	long long	result;
	int			sign;
	const char	*digits;

	result = 0;
	sign = 1;
	*overflow = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	digits = str;
	if (is_out_of_range(digits, sign))
		return (*overflow = 1, 0);
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

static int	exit_with_code(char **argv, t_shell *shell)
{
	long long	code;
	int			overflow;

	code = ft_atoll_safe(argv[1], &overflow);
	if (overflow)
	{
		print_error("exit", argv[1], "numeric argument required");
		shell->should_exit = 1;
		shell->exit_status = 2;
		return (2);
	}
	shell->should_exit = 1;
	shell->exit_status = (unsigned char)code;
	return ((unsigned char)code);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (!argv[1])
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (!is_numeric(argv[1]))
	{
		print_error("exit", argv[1], "numeric argument required");
		shell->should_exit = 1;
		shell->exit_status = 2;
		return (2);
	}
	if (argv[2])
	{
		print_error("exit", NULL, "too many arguments");
		shell->exit_status = 1;
		return (1);
	}
	return (exit_with_code(argv, shell));
}
