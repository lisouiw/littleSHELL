/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_two_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 06:28:50 by ltran             #+#    #+#             */
/*   Updated: 2017/09/05 17:59:11 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_nb_word(const char *s, char c, char d)
{
	int			i;
	int			word;

	i = -1;
	word = 0;
	while (s[++i] != '\0')
	{
		while (s[i] != c && s[i] != d)
		{
			i++;
			if (s[i] == c || s[i] == d)
				word++;
			if (s[i] == '\0')
				return (++word);
		}
	}
	return (word);
}

static int		ft_size_w(char const *s, char c, char d, int i)
{
	int			nb;

	nb = 0;
	while (s[i] != '\0' && s[i] != c && s[i++] != d)
		nb++;
	return (nb);
}

char			**strsplit_two_c(char const *s, char c, char d)
{
	char	**spl;
	int		w;
	int		t;
	int		i;

	if (!s)
		return (NULL);
	w = ft_nb_word(s, c, d);
	t = 0;
	i = -1;
	if (!(spl = (char**)malloc(sizeof(char *) * (w + 1))))
		return (NULL);
	while (s[++i] != '\0' && t != w)
	{
		if (s[i] == c || s[i] == d)
			;
		else
		{
			spl[t++] = ft_strsub(s, i, ft_size_w(s, c, d, i));
			i += ft_size_w(s, c, d, i);
		}
	}
	spl[t] = NULL;
	return (spl);
}
