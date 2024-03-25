/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:57:39 by istili            #+#    #+#             */
/*   Updated: 2024/02/28 03:32:47 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_handler(int sig)
{
	if (sig == SIGUSR2)
		write(1, "Got the msg\n", 12);
}

static void	send_char(int pid, char c)
{
	unsigned char	byte;
	int				i;

	byte = (unsigned char )c;
	i = 7;
	while (i >= 0)
	{
		if (byte >> i & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				return (write(1, "Error sending signal\n", 21), exit(1));
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				return (write(1, "Error sending signal\n", 21), exit(1));
		}
		usleep(300);
		i--;
	}
}

void	sender(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		send_char(pid, str[i++]);
	send_char(pid, str[i]);
}

int	main(int ac, char **av)
{
	int					id;

	if (ac != 3 || !is_number(av[1]))
		return (write(1, "Arguments invalid!\n", 19), 1);
	if (signal(SIGUSR2, sig_handler) == SIG_ERR)
		return (write(1, "Signal function failed!\n", 24), exit(1), 1);
	id = ft_atoi(av[1]);
	sender(id, av[2]);
	return (0);
}
