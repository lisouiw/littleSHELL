/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/08/01 05:29:26 by ltran            ###   ########.fr       */
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

void	b_echo(char **line, int i)
{
	int		a;

	a = len_double(line, -1);
	if (a == 0)
		write(1, "\n", 1);
	if ((line[1][0] == '"' && line[a][ft_strlen(line[a])-1] == '"') ||
		(line[1][0] == 39 && line[a][ft_strlen(line[a])-1] == 39))
	{
		line[a][ft_strlen(line[a])-1] = '\n';
		ft_putstr(&line[1][1]);
		while (line[++i])
		{
			write(1, " ", 1);
			ft_putstr(line[i]);
		}
	}
	else
		ft_putendl(line[a]);
}

void	double_char(char **ar, int i)
{

	while (ar[++i])
		ft_putendl(ar[i]);
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

void	b_cd(char **way, char *home, char *pwd)
{
	int		a;
	pid_t	father;
	char	buf[101];

	printf("PWD = %s HOME %s\n", pwd, home);
//cd: not a directory: [file]
//cd : no such file or directory: [file]
	getcwd(buf, 100);
	printf("BUF = %s\n", buf);
	if ((a = len_double(way,0) == 2))
	{
		ft_putstr("cd : string not in pwd : ");
		ft_putendl(way[1]);
	}
	if (a > 2)
		ft_putstr("cd : too many arguments\n");
	if (a == 0)
	{
		if (ft_strlen(home) > ft_strlen(pwd))
			chdir(pwd);
		else
		{
			chdir("/Users/ltran/littleSHELL/libft/");
		}
	}
	//modifier le env
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


	i = 0;
//	chdir("..");
//	printf("BUF -> %s\n", buf);
	while (env[i] && !(path = ft_strsplit(line_split("PATH=", env[i]), ':')))
		++i;
	i = 0;
	while (env[i] && !(home = line_split("HOME=", env[i])))
		++i;
	i = 0;
	while (env[i] && !(pwd = line_split("PWD=", env[i])))
		++i;
//	while (path[++i])
//		printf("-> %s\n", path[i]);
	while (42)
	{
		ft_putstr("(.Y.)> ");
		if (get_next_line(0, &line) && ft_strcmp(line, "exit") == 0)
			exit(0);
		else
		{
			i = -1;
			argv = ft_strsplit(line, ' ');
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
	}
	return (0);
}














