/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:23:59 by istili            #+#    #+#             */
/*   Updated: 2024/02/24 17:35:06 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
				write(1, "Error sending signal\n", 21);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				write(1, "Error sending signal\n", 21);
		}
		if (usleep(200) == -1)
			write(1, "Error sleeping\n", 15);
		i--;
	}
}

void	sender(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		send_char(pid, str[i++]);
}

int	main(int ac, char **av)
{
	int	id;

	if (ac != 3 || !is_number(av[1]))
		return (write(1, "Arguments invalid!\n", 19), 1);
	id = ft_atoi(av[1]);
	sender(id, av[2]);
	return (0);
}
