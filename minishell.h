/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:13:36 by ltran             #+#    #+#             */
/*   Updated: 2017/08/28 05:43:53 by ltran            ###   ########.fr       */
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

typedef struct			s_env
{
	char				*name;
	char				*ctn;
	struct s_env		*next;
}						t_env;


void	free_list(t_env *env);
t_env	*add_env(char *environ, t_env *env, size_t one, size_t all);
void	ecriture_info(t_env *lst);
t_env	*give_env(t_env *env);
char	**strsplit_two_c(char const *s, char c, char d);
void	give_old(t_env **env, int i);
void	b_cd(char *cd, t_env *env, char *last);
void	change_env(t_env **env, char *buf);

#endif
