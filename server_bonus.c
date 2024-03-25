/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:57:13 by istili            #+#    #+#             */
/*   Updated: 2024/02/28 03:30:03 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	kat_dir_bzero(t_data *data)
{
	ft_bzero(data->buffer, 4);
	data->i = 0;
	data->nb_byte = 0;
}

static void	unicode(t_data *data)
{
	if (data->i == 0)
	{
		if (data->current_char >= 240)
			data->nb_byte = 4;
		else if (data->current_char >= 224)
			data->nb_byte = 3;
		else if (data->current_char >= 192)
			data->nb_byte = 2;
	}
	if (data->nb_byte && data->i < data->nb_byte)
		data->buffer[data->i++] = data->current_char;
	if (data->nb_byte && data->i == data->nb_byte)
	{
		write(1, data->buffer, data->nb_byte);
		kat_dir_bzero(data);
	}
}

static void	sig_received(pid_t client_pid)
{
	if (kill(client_pid, SIGUSR2) == -1)
	{
		write(1, "Could not send it\n", 18);
		exit(1);
	}
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static t_data	data;

	(void)context;
	if (!data.client_pid)
		data.client_pid = info->si_pid;
	if (info->si_pid != data.client_pid)
	{
		data.client_pid = info->si_pid;
		data.current_char = 0;
		data.bit_count = 0;
		kat_dir_bzero(&data);
	}
	data.current_char = data.current_char << 1 | (sig == SIGUSR2);
	data.bit_count++;
	if (data.bit_count == 8)
	{
		if (data.current_char == '\0')
			sig_received(data.client_pid);
		else if (data.current_char > 127)
			unicode(&data);
		else
			ft_putchar(data.current_char);
		data.bit_count = 0;
		data.current_char = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_handler = NULL;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	pid = getpid();
	ft_putstr("Server pid: ");
	ft_putnbr(pid);
	ft_putstr("\n");
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(1, "sigaction error\n", 16), 1);
	while (1)
		pause();
}
