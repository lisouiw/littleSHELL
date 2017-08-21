/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/08/21 17:22:22 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

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
int		len_double(char **ar, int i)
{
	int		len;

	len = 0;
	while (ar[++i])
		++len;
	return (len);
}





char	*line_split(char *len, char *str)
{
	int		i;

	i = 0;
	while (len[i] && len[i] == str[i])
		++i;
	if (!len[i])
	{
		while (--i != -1)
			++str;
		return (str);
	}
	return (NULL);
}

void	b_export()
{
	//export NAME=name NAME=name
}

void	b_cd(char **way, char *home, char *pwd)
{
	int		a;
	pid_t	father;
	char	buf[101];
	int		i;
	char	*str;

//need modification du env a chaque desplacement| pwd previous |
//cd: not a directory: [file]
//cd : no such file or directory: [file]
//cd ~(HOME) | cd - (switch previous dir) |cd ~ltran
//no need modifier { cd / |
//cd ~user |cd / Users/login|
	getcwd(buf, 100);
	printf("PWD/BUF = %s HOME %s\n", pwd, home);
	str = ft_strjoin(ft_strjoin(buf, "/"), way[1]);
	if (!opendir(str))
	{
		if (open(str, O_RDONLY) == -1)
			ft_putstr("cd : no such file or directory: [file]\n");
		else
			ft_putstr("cd : not a directory: [file]\n");
	}
	if ((a = len_double(way,0)) == 2)
	{
		printf("A %i\n", a);
		ft_putstr("cd : string not in pwd : ");
		ft_putendl(way[1]);
	}
	printf("A %i\n", a);
	if (a > 2)
		ft_putstr("cd : too many arguments\n");
	if (a == 0 || a == 1 )
	{
		chdir("/");
		if (a == 0 || ft_strcmp(way[1], "~") == 0 || ft_strcmp(way[1], "--") == 0)
		{
			printf("~\n");
			chdir(home);
		}
	//	else if (ft_strcmp(way[1], "/") == 0)
	//		printf("/\n");
		else
		{
			printf("LET IT GO\n");
			chdir(str);
		}
	}

	//modifier le env
}

void	double_char(char **ar, int i)
{

	while (ar[++i])
		ft_putendl(ar[i]);
}

void	b_echo(char **line, int i)
{
	int		a;

	a = len_double(line, -1);
	if (a == 0)
		write(1, "\n", 1);
	while((a = quote()) != 0)
		a == 1 ? ft_putstr("quote> ") : ft_putstr("dquote> ");
}

void	exec_cmd(char **line)
{
	if (ft_strcmp("echo", line[0]) == 0)
		b_echo(line, 1);
	if (ft_strcmp("env", line[0]) == 0)
		;
	if (ft_strcmp("export", line[0]) == 0)
		;
	if (ft_strcmp("unsetenv", line[0]) == 0)
		;
	if (ft_strcmp("cd", line[0]) == 0)
		;
	else
		;
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	int		i;
	int		w;
	char	*cm;
	pid_t	father;
	char	**path = NULL;
	char	*home;
	char	*pwd;

	//env recup avec liste chainee
	while (42)
	{
		ft_putstr("(.Y.)> ");
		if (get_next_line(0, &line) && ft_strcmp(line, "exit") == 0)
			exit(0);
		else
			exec_cmd(/*argv = i*/ft_strsplit(line, ' '));
	}
	return (0);
}












/*
		else
		{
			i = -1;
			if (line_split("env", argv[0]) != NULL)
				double_char(env, -1);
			if (line_split("echo", argv[0]) != NULL)
				b_echo(argv, 1);
			if (line_split("cd", argv[0]) != NULL)
				b_cd(argv, home, pwd);
			else
			{
				cm = ft_strjoin("/bin/", argv[0]);
				father = fork();
				waitpid(father, &w, 0);
				if (father == 0)
					execve(cm, argv, NULL);
			}
		//	free(argv);
		//	free(line);
		}
*/
