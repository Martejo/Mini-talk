/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:54:09 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/10 08:54:09 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	confirm_msg(int signal)
{
	ft_printf("Ok\n");
	if (signal == SIGUSR2)
		ft_printf("message recieved\n");
}

void	send_bits(int pid, char bit)
{
	if (bit == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100); // Petit délai pour permettre au serveur de traiter le signal
	
}

void	find_bit(int pid, char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = (c >> i) & 1;
		send_bits(pid, bit);
		i++;
	}
	
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	

	if (argc != 3 || !argv[2])
	{
		ft_putstr_fd("Usage: client <PID Serveur> <Message>\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	pid = ft_atoi(argv[1]);
	if (pid == -1)
	{
		ft_putstr_fd("Error: Pid serveur.\n", 2);
		exit(EXIT_FAILURE);
	}
	while (argv[2][i])
	{
		find_bit(pid, argv[2][i]);
		i++;
	}
	signal(SIGUSR2, confirm_msg);
	find_bit(pid, '\n');
	return (0);
}