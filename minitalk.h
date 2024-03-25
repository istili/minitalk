/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:34:54 by istili            #+#    #+#             */
/*   Updated: 2024/02/24 17:17:12 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int		i;
	char	buffer[4];
	int		nb_byte;
	int		current_char;
	pid_t	client_pid;
	int		bit_count;
}			t_data;

void	sender(int pid, char *str);
void	handler(int sig, siginfo_t *info, void *context);
int		is_number(char *s);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *s);

#endif
