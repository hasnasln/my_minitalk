/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:30:08 by haslan            #+#    #+#             */
/*   Updated: 2024/01/08 10:16:00 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static int	ft_atoi(const char *str)
{
	int	sing;
	int	result;

	result = 0;
	sing = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sing = 1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	if (sing)
		return (result * (-1));
	return (result);
}

static void	signal_pid(int pid, unsigned int cpid)
{
	unsigned int	step;

	step = 2147483648;
	while (step >= 1)
	{
		if ((cpid / step) % 2 == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		step /= 2;
	}
}

static void	signal_char(int pid, unsigned int c)
{
	int	step;

	step = 128;
	while (step >= 1)
	{
		if ((c / step) % 2 == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		step /= 2;
	}
}

static void	come_back(int bit)
{
	if (bit == SIGUSR2)
		write(1, "Signal received\n", 16);
}

int	main(int argc, char *argv[])
{
	int				pid;
	int				i;
	unsigned int	cpid;

	i = 0;
	if (argc != 3)
	{
		write(1, "$---------------------------------$\n", 36);
		write(1, "~> ./client <PID> <STRING to send>\n", 35);
		write(1, "$---------------------------------$\n", 36);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid == -1)
		return (0);
	cpid = getpid();
	signal_pid(pid, cpid);
	signal(SIGUSR2, come_back);
	while (argv[2][i] != '\0')
	{
		signal_char(pid, argv[2][i]);
		i++;
	}
	signal_char(pid, '\0');
	return (0);
}
