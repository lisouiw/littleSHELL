/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:13:36 by ltran             #+#    #+#             */
/*   Updated: 2017/09/18 14:48:44 by ltran            ###   ########.fr       */
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

typedef struct		s_env
{
	char			*name;
	char			*ctn;
	struct s_env	*next;
}					t_env;

typedef struct		s_ec
{
	size_t		len;
	char		*add;
	char		*line;
	char		**cut;
	char		*tmp;
	int		a;
	int		i;
}					t_ec;

t_env				*exec_cmd(char *line, t_env *env, char **cut, int *i);
void				b_other(char **cut, t_env *env);
char				**list_to_tab(t_env *env, char **tab_env);
int					give_path(t_env *env, char **cut, int i, char **tab_env);
t_env				*give_env(t_env *env);
t_env				*add_env(char *environ, t_env *env, size_t one, size_t all);
void				free_elem(t_env *tmp);
void				b_export(char *cut, t_env **env);
void				b_unset(char **cut, t_env **env, int i);
void				cd_prev(t_env **env, char *buf);
void				cd_home(t_env **env, char *buf);
void				cd_name(t_env **env, char *cd, char *user, char *buf);
void				cd_simple(t_env **env, char *cd, char *buf, char *real);
void				b_cd(char *cd, t_env **env);
char				**strsplit_two_c(char const *s, char c, char d);
void				b_echo_w(char *rd, t_env *env, char *line, int o);
char				*give_echo(t_ec e, int *o, char *rd, t_env *var);
void				give_chg(char *rd, int *a, t_env **var, int *i);
void				free_echo(char **add, char **tmp, char ***cut, t_env **var);
t_env				*var_and_len(char **cut, t_env *env, size_t *len);
t_env				*give_var(char *cut, t_env *env, t_env *var, int i);
int					give_i(char *cut, int i, int *c);
t_env				*add_var(char *ctn, t_env *var);
size_t				give_len(char *cut, size_t len, int i);
int					free_for_exit(char *line, char **cut, t_env *env);
void				double_char_c(char **ar, int i, char c);
void				free_tab(char **array);
char				*t_strjoin(char *f, char *s, char *t);
void				free_list(t_env **env);
void				*no_b_spc(char *s);
void				ecriture_info(t_env *lst);
void				*cpy(char *dst, char *src);


#endif
