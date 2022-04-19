/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:25:09 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/19 17:27:18 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(t_command *command)
{
	int	i;

	i = -1;
	if (command != 0)
	{
		if (command->args != 0)
		{
			while (command->args[++i] != 0)
				free(command->args[i]);
			free(command->args);
		}
		if (command->oper != 0)
			free(command->oper);
		if (command->oper_value != 0)
			free(command->oper_value);
		if (command->heredoc != 0)
			free(command->heredoc);
		free(command);
	}
}
