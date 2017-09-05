/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:29:27 by ltran             #+#    #+#             */
/*   Updated: 2017/09/05 18:14:19 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_echo(char *join2, int *o, char *rd, int i)
{
	int		a;

	a = -1;
	if (!(join2 = (char*)malloc((ft_strlen(rd) + 1) * sizeof(char))))
		return (NULL);
	while (rd[++a])
	{
		if (rd[a] == 39 && *o < 2)
			*o = (*o == 0) ? 1 : 0;
		else if (rd[a] == '"' && (*o == 0 || *o == 2))
			*o = (*o == 0) ? 2 : 0;
		else if (rd[a] != '"' && rd[a] != 39 && rd[a] != ' ' && rd[a] != '\t')
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && *o != 0)
			join2[i++] = rd[a];
		else if ((rd[a] == '"' && *o == 1) || (rd[a] == 39 && *o == 2))
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && join2[i - 1] != ' '
				&& *o == 0)
			join2[i++] = ' ';
	}
	join2[i] = '\n';
	join2[i + 1] = '\0';
	return (join2);
}

void	b_echo(char *join, int o, char *rd)
{
	char		*line;
	char		*tmp;
	char		*join2;

	join2 = NULL;
	if ((join2 = give_echo(join2, &o, rd, 0)) == NULL)
		return ;
	tmp = ft_strjoin(join, join2);
	if (o == 0)
	{
		tmp == NULL ? ft_putstr(join2) : ft_putstr(tmp);
		ft_strdel(&join2);
		ft_strdel(&tmp);
	}
	else
	{
		o == 1 ? ft_putstr("quote> ") : ft_putstr("dquote> ");
		get_next_line(0, &line);
		b_echo(join2, o, line);
		ft_strdel(&join2);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
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
