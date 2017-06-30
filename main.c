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

int		main(int ac, char **av)
{
	char		*buf;
	int			w;
	size_t		i;
	pid_t	father;


	father = fork();

	while (ft_strcmp(av[1], "exit") != 0)
	{
		if (father > 0)
		{
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
			kill(father, w);
			printf("SIGNAL = %i\n", w);
		}
		if (father ==  0)
		{
			printf("$> ");
			waitpid(father, &w, &i);
		}
	}
	return (0);
}
