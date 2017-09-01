/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:13:36 by ltran             #+#    #+#             */
/*   Updated: 2017/09/01 15:09:33 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>

typedef struct			s_env
{
	char				*name;
	char				*ctn;
	struct s_env		*next;
}						t_env;


void	free_list(t_env *env);
t_env	*add_env(char *environ, t_env *env, size_t one, size_t all);
void	ecriture_info(t_env *lst);
char	**strsplit_two_c(char const *s, char c, char d);
void	b_cd(char *cd, t_env *env, char *last);
void	cd_prev(t_env *tmp);
t_env	*create_env(t_env *env);


t_env	*give_env(t_env *env);
t_env	*add_env(char *environ, t_env *env, size_t one, size_t all);
t_env	*exec_cmd(char *line, t_env *env);
void	*no_b_spc(char *s);
void	b_echo(char *join, int o, char *rd);

#endif
