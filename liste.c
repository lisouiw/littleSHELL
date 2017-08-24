/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecriture.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:16:01 by ltran             #+#    #+#             */
/*   Updated: 2017/08/24 16:47:21 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ecriture_info(t_env *lst)
{
	while (lst->next != NULL)
	{
		ft_putstr(lst->name);
		ft_putendl(lst->ctn);
		lst = lst->next;
	}
}
