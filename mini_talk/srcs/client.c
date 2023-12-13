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

int	g_bit_handler;

void	validation_server(int signal)
{
	if (signal == SIGUSR2)
	{
		ft_printf("Message sent and received.\n");
		exit(EXIT_SUCCESS);
	}
	else if (signal == SIGUSR1)
		g_bit_handler = 1;
}

int	check_args(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3 || !argv[2][0])
	{
		ft_putstr_fd("Error arguments, please try again.\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid == 0)
	{
		ft_putstr_fd("Error: PID 0 is reserved for the kernel.\n", 2);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (argv[1][++i])
	{
		if (!(ft_isdigit(argv[1][i])) || pid < 0)
		{
			ft_putstr_fd("Error: a PID only has positive decimal numbers.", 2);
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}

void	send_bit(pid_t pid, unsigned char c)
{
	int	bit;

	bit = __CHAR_BIT__ * sizeof(c) - 1;
	while (bit >= 0)
	{
		g_bit_handler = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_bit_handler != 1)
			usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	pid = check_args(argc, argv);
	i = -1;
	signal(SIGUSR1, validation_server);
	signal(SIGUSR2, validation_server);
	while (argv[2][++i])
		send_bit(pid, argv[2][i]);
	send_bit(pid, '\n');
	send_bit(pid, 0);
	while (1)
		pause();
}
