/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 23:51:35 by ltran             #+#    #+#             */
/*   Updated: 2017/08/21 17:22:24 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*beginchr(const char *s, int c)
{
	int		i;

	i = 0;

	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i++] == c)
		return (ft_strsub(s, 0, i));
	return (NULL);
}

int		main(int ac, char **av)
{
	char	*str;

	str = beginchr("sjskssk=", '=');
	printf("%c\n", 0);
	return (0);
}





