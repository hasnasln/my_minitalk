/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:35:55 by haslan            #+#    #+#             */
/*   Updated: 2024/01/03 15:24:22 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

struct s_incoming
{
	unsigned long		value;
	int					len;
	int					max;
	int					flag;
	int					wflag;
	int					cpid;
	int					cpid_len;
	char				str[5];
};
#endif