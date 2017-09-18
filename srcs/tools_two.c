/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:37:20 by ltran             #+#    #+#             */
/*   Updated: 2017/09/18 14:51:06 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*cpy(char *dst, char *src)
{
	int		i;
	int		a;

	a = -1;
	i = 0;
	if (dst != NULL)
		while (dst[++a] != '\0')
			;
	while (src[i] != '\0')
	{
		dst[a] = src[i];
		i++;
		++a;
	}
	dst[a] = '\0';
	return (dst);
}

void	ecriture_info(t_env *lst)
{
	if (!(lst))
		return ;
	while (lst->next != NULL)
	{
		ft_putstr(lst->name);
		ft_putendl(lst->ctn);
		lst = lst->next;
	}
	ft_putstr(lst->name);
	ft_putendl(lst->ctn);
}

void	*no_b_spc(char *s)
{
	int		i;
	char	*b;

	i = 0;
	b = (char*)s;
	while ((b[i] == ' ' || b[i] == '\t') && b[i] != '\0')
		++i;
	i += 4;
	while ((b[i] == ' ' || b[i] == '\t') && b[i] != '\0')
		++i;
	return (&b[i]);
}
