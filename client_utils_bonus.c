/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:56:55 by istili            #+#    #+#             */
/*   Updated: 2024/02/24 17:35:31 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		return (0);
	if (!s[i])
		return (0);
	if (s[i] == '0' && s[i + 1] == '\0')
		return (0);
	while (s[i] && ft_isdigit(s[i]) == 1)
		i++;
	if (!s[i])
		return (1);
	else
		return (0);
}

static int	check_sign(const char *str, int i)
{
	int	sign;

	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	long	nb;
	long	tmp;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\n' || str[i] == ' ')
		i++;
	sign = check_sign(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	nb = 0;
	while (ft_isdigit(str[i]))
	{
		tmp = nb * 10 + str[i] - '0';
		if (nb > tmp && sign == 1)
			return (-1);
		if (nb > tmp && sign == -1)
			return (0);
		nb = tmp;
		i++;
	}
	return (nb * sign);
}
