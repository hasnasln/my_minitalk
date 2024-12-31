/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:29:52 by haslan            #+#    #+#             */
/*   Updated: 2024/01/03 15:14:59 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "server.h"

struct s_incoming	g_incoming = {0, 0, 0, 0, 0, 0, 0, ""};

static void	get_pid(int bit)
{
	if (bit == SIGUSR1)
		g_incoming.cpid = g_incoming.cpid * 2 + 1;
	else if (bit == SIGUSR2)
		g_incoming.cpid = g_incoming.cpid * 2 + 0;
	g_incoming.cpid_len++;
}

static void	send_rsignal(void)
{
	write(1, "\n", 1);
	kill(g_incoming.cpid, SIGUSR2);
	g_incoming.cpid = 0;
	g_incoming.cpid_len = 0;
	g_incoming.wflag = 0;
}

static void	ft_putchar(int bit)
{
	if (bit == SIGUSR1)
		g_incoming.value = g_incoming.value * 2 + 1;
	else if (bit == SIGUSR2)
	{
		g_incoming.value = g_incoming.value * 2 + 0;
		if (g_incoming.flag == 0)
			g_incoming.max = g_incoming.len * 8;
		g_incoming.flag = 1;
		if (g_incoming.max == 0)
			g_incoming.max = 8;
	}
	g_incoming.len += 1;
	if (g_incoming.len % 8 == 0)
		g_incoming.str[(g_incoming.len / 8) - 1] = g_incoming.value % 256;
	if (g_incoming.max == g_incoming.len)
	{
		if (g_incoming.value == '\0')
			send_rsignal();
		else
			write(1, g_incoming.str, g_incoming.len / 8);
		g_incoming.value = 0;
		g_incoming.len = 0;
		g_incoming.max = 0;
		g_incoming.flag = 0;
	}
}

static void	ft_putnbr(int pid)
{
	if (pid > 9)
		ft_putnbr(pid / 10);
	write(1, &"0123456789"[pid % 10], 1);
}

int	main(void)
{
	write (1, "-------------------\nServer PID: ", 32);
	ft_putnbr(getpid());
	write (1, "\n-------------------\n", 22);
	while (1)
	{
		if (g_incoming.cpid_len == 32 && !g_incoming.wflag)
		{
			write(1, "There is a message from --> ", 28);
			ft_putnbr(g_incoming.cpid);
			g_incoming.wflag = 1;
			write(1, "\n---------------------------  ---\n--> ", 39);
		}
		if (g_incoming.cpid_len != 32)
		{
			signal(SIGUSR1, get_pid);
			signal(SIGUSR2, get_pid);
		}
		else
		{
			signal(SIGUSR1, ft_putchar);
			signal(SIGUSR2, ft_putchar);
		}
		pause();
	}
}
