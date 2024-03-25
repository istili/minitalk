/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:00:42 by istili            #+#    #+#             */
/*   Updated: 2024/02/24 17:52:20 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putchr(char c)
{
	if (write(1, &c, 1) == -1)
		write(1, "write error\n", 12);
}

static void	ft_putnb(int n)
{
	int	i;

	i = 0;
	if (n >= 10)
	{
		ft_putnb(n / 10);
		ft_putnb(n % 10);
	}
	else
		ft_putchr(n + '0');
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int		bit_count = 0;
	static char		current_char = 0;
	static pid_t	client_pid;

	if (!client_pid)
		client_pid = info->si_pid;
	if (info->si_pid != client_pid)
	{
		client_pid = info->si_pid;
		current_char = 0;
		bit_count = 0;
	}
	current_char = current_char << 1 | (sig == SIGUSR2);
	bit_count++;
	if (bit_count == 8)
	{
		ft_putchr(current_char);
		bit_count = 0;
		current_char = 0;
	}
	(void)context;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_handler = NULL;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	pid = getpid();
	write(1, "Server pid: ", 11);
	ft_putnb(pid);
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		write(1, "sigaction error\n", 16);
	while (1)
	{
		pause();
	}
}
