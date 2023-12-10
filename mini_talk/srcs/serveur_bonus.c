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

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static	int	c;
	static	int	bit;
	
	(void)context;
	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", c);
		c = 0;
		bit = 0;
		kill(info->si_pid, SIGUSR2);
	}
}
int main(int argc, char **argv)
{
	int	pid;
	struct sigaction	sig;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error.\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = getpid();
	sig.sa_sigaction = handle_signal;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	if (pid == -1)
	{
		ft_putstr_fd("Error getpid.\n", 2);
		exit(EXIT_FAILURE);
	}
	printf("pid du processus = %d\n", pid);
	
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}