/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:12:51 by ltran             #+#    #+#             */
/*   Updated: 2017/08/30 18:16:03 by ltran            ###   ########.fr       */
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

/*
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
}*/

void	double_char(char **ar, int i)
{
	while (ar[++i])
		ft_putendl(ar[i]);
}

void	double_char_c(char **ar, int i, char c)
{
	while (ar[++i])
	{
		ft_putstr(ar[i]);
		ft_putchar(c);
	}
	write(1, "\n", 1);
}

void	my_strjoin(char **spc, char **line, int a)
{
	char	*tmp;

	if (line[a] && !(line [a + 1]))
		*spc = line[a];
	while (line[a] && line [a + 1])
	{
		if (*spc != NULL)
			tmp = ft_strjoin(*spc, " ");
		else
			tmp = ft_strjoin(line[a], " ");
		*spc = ft_strjoin(tmp, line[a + 1]);
		++a;
	}
}

size_t	all_d_len(char **echo, int a)
{
	int			o;
	size_t		len;

	while (echo[++a])
	{
		o = -1;
		while (echo[a][++o])
			;
		len += o;
	}
	len = len + a + 1;
	return (len);
}

void	b_export(char **cut, t_env **env)
{
	int		i;
	t_env	*tmp;
	t_env	*kp;

	i = 0;
	while (cut[++i])
	{
		kp = *env;
		if ((ft_strchr(cut[i], '=')))
		{
			tmp = (t_env*)malloc(sizeof(t_env));
			tmp = NULL;
			tmp = add_env(cut[i], tmp, ft_strlen(ft_strchr(cut[i], '=')),
				ft_strlen(cut[i]));
			while (kp->name != NULL && kp->next != NULL && ft_strcmp(kp->name, tmp->name) != 0)
				kp = kp->next;
			if (kp->name == NULL || ft_strcmp(kp->name, tmp->name) == 0)
			{
				free(kp->name);
				kp->name = ft_strdup(tmp->name);
				free(kp->ctn);
				kp->ctn = ft_strdup(tmp->ctn);
				free_list(tmp);
			}
			else
			{
				*env = add_env(cut[i], *env, ft_strlen(ft_strchr(cut[i], '=')),
					ft_strlen(cut[i]));
			}
		}
	}
}


void	give_path(t_env *env, char **cut)
{
	char	**path;
	int		i;
	char	*cmd;
	pid_t	father;
	int		w;
	int		y;
	int		a;

	a = -1;
	i = -1;
	while (env->next != NULL && ft_strcmp("PATH=", env->name) != 0)
		env = env->next;
	if (ft_strcmp("PATH=", env->name) == 0 && (path = ft_strsplit(env->ctn, ':')))
		father = fork();
	while (path[++i] && a == -1)
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, cut[0]);
		waitpid(father, &w, 0);
		if ((a = access(cmd, F_OK)) == 0 && father == 0)
		{
			execve(cmd, cut, NULL);
			free(cmd);
		}
	}
	if (a == -1)
	{
//		kill(father, y);
		ft_putstr("sh : command not found: ");
		ft_putendl(cut[0]);
	}
}

void	b_other(char **cut, t_env *env)
{
	pid_t	father;
	int		w;

	if (access(cut[0], F_OK) == 0)
	{
		father = fork();
		if (waitpid(father, &w, 0) && father == 0)
			execve(cut[0], cut, NULL);
	}
	else
			give_path(env, cut);
}

void	b_echo(char **echo, char *join, int o, char *rd)
{
	int			i;
	char		*line;
	char		*join2;
	int			a;

	a = -1;
	i = 0;
	if(!(join2 = (char*)malloc((ft_strlen(rd) + 1)*sizeof(char))))
		return;
	while (rd[++a])
	{
		if (rd[a] == 39 && o < 2)
			o = (o == 0) ? 1 : 0;
		else if (rd[a] == '"' && (o == 0 || o == 2))
			o = (o == 0) ? 2 : 0;
		else if (rd[a] != '"' && rd[a] != 39 && rd[a] != ' ' && rd[a] != '\t')
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && o != 0)
			join2[i++] = rd[a];
		else if ((rd[a] == '"' && o == 1) || (rd[a] == 39 && o == 2))
			join2[i++] = rd[a];
		else if ((rd[a] == ' ' || rd[a] == '\t') && join2[i-1] != ' ' && o == 0)
			join2[i++] = ' ';
	}
	join2[i] = '\n';
	join2[i + 1] = '\0';
	if (join != NULL)
		join2 = ft_strjoin(join, join2);
	if (o == 0)
		ft_putstr(join2);
	else
	{
		o == 1 ? ft_putstr("quote> ") : ft_putstr("dquote> ");
		get_next_line(0, &line);
		b_echo(echo, join2, o, line);
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
	if (b[i] != '\0')
		return (&b[i]);
	return (NULL);
}


void	b_unset(char **cut, t_env **env)
{
	int		i;
	t_env	*kp;
	t_env	*sup;

	i = 0;

	while (cut[++i])
	{
		kp = *env;
		if (ft_strcmp(kp->name, cut[i]) == 61)
		{
			if ((*env)->next == NULL)
			{
				printf("PUTn\n");
				(*env)->name = NULL;
				(*env)->ctn = NULL;
			}
			else
			{
				sup = kp;
				*env = (*env)->next;
				sup->name = NULL;
				free(sup->name);
				free(sup->ctn);
				free(sup);
				kp = *env;
				free(sup->ctn);
			}
		}
		else
		{
			while (kp->next != NULL && ft_strcmp(kp->next->name, cut[i]) != 61)
				kp = kp->next;
			if (ft_strcmp(kp->next->name, cut[i]) == 61)
			{
				sup = kp->next;
				if (kp->next->next != NULL)
				{
					kp->next = kp->next->next;
					sup->name = NULL;
					sup->ctn = NULL;
					free(sup->name);
					free(sup->ctn);
				}
				else
				{
					sup->name = NULL;
					sup->ctn = NULL;
					free(sup->name);
					free(sup->ctn);
					kp->next = NULL;
				}
			}
		}
	}
	return;
}



t_env	*exec_cmd(char *line, t_env *env)
{
	char	**cut;

	if (!(cut = strsplit_two_c(line, '\t', ' ')) || !cut[0])
		return (env);
	if (ft_strcmp("echo", cut[0]) == 0)
	{
		if (!(cut[1]))
			write(1, "\n", 1);
		else if (ft_strchr(line , '"') == NULL && ft_strchr(line , 39) == NULL)
			double_char_c(cut, 0, ' ');
		else
			b_echo(cut, NULL, 0, no_b_spc(&line[4]));
	}
	else if (ft_strcmp("env", cut[0]) == 0)
		env->name == NULL ? 0 : ecriture_info(env);
	else if (ft_strcmp("export", cut[0]) == 0 && cut[1])
		b_export(cut, &env);
	else if (env && ft_strcmp("unset", cut[0]) == 0)
	{
		b_unset(cut, &env);
		ecriture_info(env);
	}
	else if (ft_strcmp("cd", cut[0]) == 0)
		b_cd(cut[1], env, cut[2]);
	else
		b_other(cut, env);
	return (env);
}

t_env	*add_env(char *environ, t_env *env, size_t one, size_t all)
{
	t_env	*new;
	t_env	*tmp;

	tmp = env;
	new = (t_env*)malloc(sizeof(t_env));
	new->name = ft_strsub(environ, 0, all - one + 1);
	new->ctn = ft_strsub(environ, all - one + 1, one -1);
	new->next = NULL;
	if (env == NULL)
	{
		new->next = env;
		return (new);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (env);
}

t_env	*create_env(t_env *env)
{
	env = (t_env*)malloc(sizeof(t_env));
	env->name = ft_strnew(0);
	env->name = NULL;
	env->ctn = ft_strnew(0);
	env->ctn = NULL;
	env->next = NULL;
	return (env);
}

t_env	*give_env(t_env *env)
{
	int				i;
	extern char		**environ;

	env = create_env(NULL);
	i = -1;
	while (environ[++i])
	{
		env = add_env(environ[i], env, ft_strlen(ft_strchr(environ[i], '=')),
				ft_strlen(environ[i]));
	}
	return (env);
}

void	cd_home(t_env *env)
{
	char	buf[126];
	t_env	*tmp;
	t_env	*tm;

	tmp = env;
	tm = env;
	while (ft_strcmp(tmp->name, "OLDPWD=") != 0 && tmp->next != NULL)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		free(tmp->ctn);
		getcwd(buf, 126);
		tmp->ctn = ft_strdup(buf);
	}
	while (ft_strcmp(env->name, "HOME=") != 0 && env->next != NULL)
		env = env->next;
	if (ft_strcmp(env->name, "HOME=") == 0)
		chdir(env->ctn);
	while (ft_strcmp(tm->name, "PWD=") != 0 && tm->next != NULL)
		tm = tm->next;
	if (ft_strcmp(tm->name, "PWD=") == 0)
	{
		getcwd(buf, 127);
		free(tm->ctn);
		tm->ctn = ft_strdup(buf);
	}
}

void	cd_slash(t_env *tmp, char *cd)
{
	t_env	*env;
	char	buf[126]; //test if len sup

	env = tmp;
	while (ft_strcmp(tmp->name, "OLDPWD=") != 0 && tmp->next != NULL)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		getcwd(buf, 127);
		chdir(cd);
		free(tmp->ctn);
		tmp->ctn = ft_strdup(buf);
		while (ft_strcmp(env->name, "PWD=") != 0 && env->next != NULL)
			env = env->next;
		if (ft_strcmp(env->name, "PWD=") == 0)
		{
			getcwd(buf, 127);
			free(env->ctn);
			env->ctn = ft_strdup(buf);
		}
	}
}

void	cd_name(t_env *tmp, char *cd, char *user)
{
	t_env	*env;
	char	buf[126]; //test if len sup

	user = ft_strjoin("/Users/", &cd[1]);
	env = tmp;
	while (ft_strcmp(tmp->name, "OLDPWD=") != 0 && tmp->next != NULL)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		getcwd(buf, 127);
		chdir(user);
		free(tmp->ctn);
		tmp->ctn = ft_strdup(buf);
		while (ft_strcmp(env->name, "PWD=") != 0 && env->next != NULL)
			env = env->next;
		if (ft_strcmp(env->name, "PWD=") == 0)
		{
			getcwd(buf, 127);
			free(env->ctn);
			env->ctn = ft_strdup(buf);
		}
	}
}



void	b_cd(char *cd, t_env *env, char *last)
{
	char	buf[PATH_MAX]; //test if len sup
	char	*way;
	int		i;

	getcwd(buf, PATH_MAX + 1);
	way = ft_strjoin(buf , "/");
	way = ft_strjoin(way, cd);
	if (!(opendir(way)))
		printf("MO\n");
	if (cd && ft_strcmp(cd, "-") == 0)
		cd_prev(env);
	else if ((!(cd) || ft_strcmp(cd, "~") == 0))
		cd_home(env);
	else if (cd[0] == '~')
		cd_name(env, cd, NULL);
	else if (cd[0] == '/')
		cd_slash(env, cd);
	else if (chdir(way) == -1)
		printf("ERROR\n");
}

void	cd_prev(t_env *tmp)
{
	t_env	*env;
	char	buf[126]; //test if len sup

	env = tmp;
	while (ft_strcmp(tmp->name, "OLDPWD=") != 0 && tmp->next != NULL)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		getcwd(buf, 127);
		chdir(tmp->ctn);
		free(tmp->ctn);
		tmp->ctn = ft_strdup(buf);
		while (ft_strcmp(env->name, "PWD=") != 0 && env->next != NULL)
			env = env->next;
		if (ft_strcmp(env->name, "PWD=") == 0)
		{
			getcwd(buf, 127);
			free(env->ctn);
			env->ctn = ft_strdup(buf);
		}
	}
	else
		ft_putendl("sh : cd: OLDPWD not set");
}

int		main(int argc, char **argv, char **env)
{
	char	*old;
	char	*line;
	t_env	*envs;

	envs = give_env(NULL);
	while (42)
	{
		ft_putstr("(. Y .)> ");
		if (get_next_line(0, &line) && ft_strcmp(line, "exit") == 0)
			exit(0);
		else
			envs = exec_cmd(line, envs);
		line = NULL;
		free(line);
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
