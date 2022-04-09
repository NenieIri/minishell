/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:18:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/09 16:38:46 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_lst_to_arr(t_var *env_lst)
{
	int		size;
	int		i;
	char	**arr;

	i = 0;
	size = lst_size(env_lst);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr == 0)
		return (0);
	arr[size] = 0;
	while (env_lst != 0)
	{
		arr[i++] = strjoin_base(env_lst->name, env_lst->value, '=');
		env_lst = env_lst->next;
	}
	return (arr);
}
