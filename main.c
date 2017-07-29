/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/06/30 14:25:39 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

/*
int		main(int ac, char **av)
{
	pid_t	father;
	int		a;

	father = fork();
	if (father > 0)
	{
		wait(&a);
		printf("COUCOU\n");
	}
	if (father == 0)
	{
		sleep(1);
		execve("/bin/ls", av, NULL);
//	}
	return (0);
}*/

/*
int		main(int ac, char **av)
{
	char		*buf;
	int			w;
	int		i;
	pid_t	father;


	father = fork();

//	while (ft_strcmp(av[1], "exit") != 0)
//	{
		if (father > 0)
		{
			waitpid(father, &w, i);
			if (ac > 1 && chdir(av[1]) == -1)
				printf("%s\n", strerror(errno));
			else
			{
				access(av[1], i);
				i | F_OK ? printf("Fichier ok\n"): 0;
				i | R_OK ? printf("READ ok\n"): 0;
				i | W_OK ? printf("Write ok\n"): 0;
				i | X_OK ? printf("EXe ok\n"): 0;
			}
			buf = getcwd(av[1], i);
			if (buf == NULL)
				strerror(errno);
		}
		if (father ==  0)
		{
			printf("$> ");
		}
//	}
	return (0);
}*/

/*
int		main(int ac, char **av)
{
	int		w;
	pid_t		father;

	father = fork();

	if (father > 0)
	{
		printf("PAPA = %i\n", father);
	}
	if (father == 0)
	{
		printf("fils = %i\n", father);
		execve("/bin/ls", av, NULL);
	}
	father = fork();
	if (father > 0)
		waitpid(father, &w, 0);
	else 
		waitpid(father, &w, 0);
	return (0);
}
*/

char	**strcmp_len(char *len, char *str)
{
	int		i;

	i = 0;
	while (len[i] && len[i] == str[i])
		++i;
	if (!len[i])
	{
		while (--i != -1)
			++str;
		return (ft_strsplit(str, ':'));
	}
	return (NULL);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	int		i = 0;
	int		w;
	char	*cm;
	pid_t	father;

	while (env[i] && (argv = strcmp_len("PATH=", env[i])) == NULL)
		++i;
	while (42)
	{
		ft_putstr("(.Y.)> ");
		if (get_next_line(0, &line) && ft_strcmp(line, "exit") == 0)
			exit(0);
		else
		{
			argv = ft_strsplit(line, ' ');
			cm = ft_strjoin("/bin/", argv[0]);
			father = fork();
			waitpid(father, &w, 0);
			if (father == 0)
				execve(cm, argv, NULL);
		}
	}
	return (0);
}


































