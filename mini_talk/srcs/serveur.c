/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:41:57 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/09 14:41:57 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <stdio.h>

void	handle_signal(int signal)
{
	static	int	c;
	static	int	bit;
	
	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", c);
		c = 0;
		bit = 0;
	}
}
int main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error.\n", 2);
	}
	pid = getpid();
	if (pid == -1)
	{
		ft_putstr_fd("Error getpid.\n", 2);
		exit(EXIT_FAILURE);
	}
	printf("pid du processus = %d\n", pid);
	
	while (argc == 1)
	{
		signal(SIGUSR1, handle_signal);
		signal(SIGUSR2, handle_signal);
		pause();
	}
	return (0);
}