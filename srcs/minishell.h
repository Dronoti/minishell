/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 08:36:54 by bkael             #+#    #+#             */
/*   Updated: 2021/11/14 16:00:13 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

int		g_code;

typedef struct s_p
{
	int		save_in;
	int		start;
	int		end;
	int		children;
	int		fd1[2];
	int		fd2[2];
	int		last;
	int		pid;
	char	**copy;
	char	***tokens;
	char	***c_env;
	char	*cmd;
	char	*prompt;
}				t_p;

typedef struct s_var
{
	int		key_len;
	int		value_len;
	char	*key;
	char	*value;
}	t_var;

void	ft_errors(char *msg, int code);
int		ft_strlen(char *s);
void	ft_putendl_fd(char *s, int fd);
void	ft_handler(int signum);
char	*ft_join_shell(char *s1, char *s2);
char	*ft_create_prompt(char **c_env);
char	*ft_strndup(char *s1, int n);
char	**ft_split(char *s, char c);
char	*ft_substr(char *s, int start, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
char	**ft_create_env(char **env);
void	ft_free_env(char **c_env);
void	ft_print_env(char **c_env);
void	ft_init_signals(void);
void	ft_free_all(char *prompt, char **c_env, char *cmd);
void	ft_parser(char **cmd, char ***c_env, char *prompt);
int		ft_exist_cmd(char *cmd);
int		ft_isvalid_quotes(char *cmd);
int		ft_isvalid_pipes_braces(char *cmd);
void	ft_check_quotes(char **newcmd, char *cmd, int *i, int *inside);
char	*ft_replace_env(char *cmd, char **c_env);
int		ft_isspace(char c);
void	ft_check_var(char **newcmd, char *cmd, int *i, char **c_env);
char	*ft_find_env(char *cmd, char **c_env, int *i);
char	*ft_join_char(char *s, char c);
char	*ft_join_env(char *s1, char *s2);
int		ft_find_key(char *key, char *str);
char	*ft_get_value(char *str);
int		ft_isvalid_key(char c);
int		ft_lennum(int n);
char	*ft_itoa(int n);
char	**ft_create_tokens(char *cmd);
int		ft_count_tokens(char *cmd);
int		ft_len_token(char *cmd);
int		ft_isspec_char(char *str);
char	**ft_free_tokens(char **tokens);
void	ft_delete_quotes(char **token, int len);
char	*ft_strjoin(char *s1, char *s2);
void	ft_remove_char(char **token, int i, int len);
int		ft_start_exec(char ***tokens, char ***c_env, char *cmd, char *prompt);
int		ft_strcmp(char *s1, char *s2);
int		ft_check_redirect(char ***tokens);
int		ft_count_redir(char **tokens);
char	**ft_init_fd(int *fd, char **tokens, int count_redir);
char	**ft_delete_redir(char **tokens, int count_redir);
int		ft_check_builtins(char **tokens, char ***c_env, int fd);
int		ft_check_bins(char **tokens, char ***c_env, int fd);
int		ft_check_pipe(char ***tokens, char ***c_env, char *cmd, char *prompt);
t_p		ft_init_arg(char ***tokens, char ***c_env, char *cmd, char *prompt);
void	ft_free_exit(char ***tokens, char ***c_env, char *cmd, char *prompt);
void	ft_child_handler(int signum);
void	ft_init_child_signals(void);
void	ft_child_quit(int signum);
void	ft_child_exit(int signum);
int		ft_init_pipes(int *fd1, int *fd2);
int		ft_run_pipe(t_p *arg);
void	ft_run_fork(t_p *arg, char **tokens, int st);
void	ft_next_pipe(int *fd1, int *fd2, int next);
int		ft_write_error(void);
int		ft_echo(char **tokens, int fd);
int		ft_pwd(int fd);
int		ft_first_ispipe(char *cmd);

int		ft_exit(char **tokens);
int		ft_cd(char **tokens, int fd);
int		ft_env(char **tokens, int fd, char **c_env);
int		ft_export(char **tokens, int fd, char ***c_env);
int		ft_unset(char **tokens, int fd, char ***c_env);

void	ft_cd_nullify_preceding_pathname(char **path_splitted, int j);
int		copy_env_vars(char **dst, char *const *src);
void	setup_var(t_var *var, char *var_str);
void	update_var(char **existing_var_record, t_var *new_var);
void	ft_extend_env(char ***env, t_var *new_var);
int		is_valid_var_key(char *key);
char	*get_str_from_symbol(char *s, char c);
void	free_cascade_var(t_var *var);
int write_single_var_line(int fd, t_var *var, char *var_str);

#endif