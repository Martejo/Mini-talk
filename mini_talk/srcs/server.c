/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:42:27 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/09 16:42:27 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <stdio.h>
#include <stdlib.h>

void	handler_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit = -1;

	(void)context;
	if (kill(info->si_pid, 0) < 0)
	{
		ft_printf("ERROR : cant send signal to pid: %d\n", info->si_pid);
		exit(EXIT_FAILURE);
	}
	if (bit < 0)
		bit = __CHAR_BIT__ * sizeof(c) - 1;
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else if (signal == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c)
		write(1, &c, 1);
	else if (!bit && !c)
		kill(info->si_pid, SIGUSR2);
	bit--;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;
	sigset_t			signals;

	pid = getpid();
	sigemptyset(&signals);
	sigaddset(&signals, SIGUSR1);
	sigaddset(&signals, SIGUSR2);
	action.sa_flags = SA_SIGINFO;
	action.sa_mask = signals;
	action.sa_handler = NULL;
	action.sa_sigaction = handler_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("PID server -> %d\n", pid);
	while (1)
		pause();
	return (0);
}
