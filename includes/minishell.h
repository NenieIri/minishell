/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:23:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/26 14:32:51 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <errno.h>

typedef struct s_var
{
	char			*name;
	char			*value;
	char			meaning;
	int				status;
	struct s_var	*next;
}					t_var;

typedef struct s_token
{
	char			type;
	char			*value;
	char			*quote;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	int					id;
	char				**args;
	char				*path;
	char				*oper;
	char				*oper_value;
	char				*heredoc;
	char				delimitor;
	int					builtin;
	int					std_in;
	int					std_in_dup1;
	int					std_out;
	int					std_out_dup1;
	int					std_err;
	struct s_command	*next;
}						t_command;

t_var		*lst_new_elem(char *name, char *value);
t_var		*lst_last(t_var *lst);
void		lst_add_back(t_var **lst, t_var *new_node);
void		lst_add_front(t_var **lst, t_var *new_elem);
void		lst_delone(t_var *lst, void (*del)(void *));
void		lst_clear(t_var **lst, void (*del)(void *));
int			lst_size(t_var *lst);

t_token		*lst_new_elem_token(char type, char *value);
t_token		*lst_last_token(t_token *lst);
void		lst_add_back_token(t_token **lst, t_token *new_node);
void		lst_delone_token(t_token *lst, void (*del)(void *));
void		lst_clear_token(t_token **lst, void (*del)(void *));
int			lst_size_token(t_token *lst);

void		shlvl(t_var **env_lst);
int			env_to_list(char **envp, t_var **env_lst);
void		change_status(t_var **env_lst, int status);
char		**env_lst_to_arr(t_var *env_lst, char meaning, int quote);
char		*strjoin_base(char const *s1, char const *s2, char c);
void		arr_free(char **arr);

int			parsing_line(char *line, t_token **tokens, t_var **env_lst);
int			tokens_count(char *line, char *metachars);
void		tokens_array(char *line, char *metachars, t_token **tokens);
void		tokens_trim(t_token **tokens);
int			parsing_command(t_token **tokens, t_command *command, \
			t_var **env_lst);
void		quote_counting(t_token *tokens);
void		p_expansion(t_token *tokens, t_var *env_lst);
void		quote_removal(t_token *tokens);
void		word_splitting(t_token **tokens, t_var *env_lst);
int			operators(t_token *tokens);
int			arg_count(t_token **tokens, t_command *command);
int			parsing_opers(t_token **tokens, t_command *command, t_var *env_lst);
void		tokens_to_struct(t_token **tokens, t_command **command, \
		t_var **env_lst);
char		*heredoc(t_command *command, t_var *env_lst);
void		command_free(t_command *command);

char		*find_command(t_command *command, t_var *env_lst);
void		exec(t_command **command, t_var **env_lst);
void		exec_builtin(t_command *command, t_var **env_lst, int child_parent);
void		child(t_command **command, t_var **env_lst, int id);
void		dups(t_command *tmp);
int			pwd(t_var **env_lst);
int			env(t_var **env_lst);
int			unset(t_command *command, t_var **env_lst);
int			export_env(t_command *command, t_var **env_lst);
int			echo(t_command *command, t_var **env_lst);
int			my_exit(t_command *command, t_var **env_lst);
int			cd(t_command *command, t_var **env_lst);

#endif
