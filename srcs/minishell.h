/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 08:36:54 by bkael             #+#    #+#             */
/*   Updated: 2021/12/07 16:00:13 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MSG_MINISHELL_EXIT "minishell: exit: "
# define NUM_ARG_REQUIRED_MSG ": numeric argument required\n"

# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

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

typedef struct s_bin
{
	pid_t		pid;
	int			i;
	char		**paths;
	char		*value;
	struct stat	buf;
}				t_bin;

typedef struct s_fds
{
	int		in_fd;
	int		out_fd;
}				t_fds;

void			ft_errors(char *msg, int code);
int				ft_strlen(char *s);
void			ft_putendl_fd(char *s, int fd);
void			ft_handler(int signum);
char			*ft_join_shell(char *s1, char *s2);
char			*ft_create_prompt(char **c_env);
char			*ft_strndup(char *s1, int n);
char			**ft_split(char *s, char c);
char			*ft_substr(char *s, int start, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memcpy(void *restrict dst, const void *restrict src,
					size_t n);
char			**ft_create_env(char **env);
void			ft_free_env(char **c_env);
char			*ft_get_value_env(char *key, char **c_env);
void			ft_init_signals(void);
void			ft_free_all(char *prompt, char **c_env, char *cmd);
void			ft_parser(char **cmd, char ***c_env, char *prompt);
int				ft_exist_cmd(char *cmd);
int				ft_isvalid_quotes(char *cmd);
int				ft_isvalid_pipes_braces(char *cmd);
void			ft_check_quotes(char **newcmd, char *cmd, int *i, int *inside);
char			*ft_replace_env(char *cmd, char **c_env);
int				ft_isspace(char c);
void			ft_check_var(char **newcmd, char *cmd, int *i, char **c_env);
char			*ft_find_env(char *cmd, char **c_env, int *i);
char			*ft_join_char(char *s, char c);
char			*ft_join_env(char *s1, char *s2);
int				ft_find_key(char *key, char *str);
char			*ft_get_value(char *str);
int				ft_isvalid_key(char c);
int				ft_lennum(int n);
char			*ft_itoa(int n);
char			**ft_create_tokens(char *cmd);
int				ft_count_tokens(char *cmd);
int				ft_len_token(char *cmd);
int				ft_isspec_char(char *str);
char			**ft_free_tokens(char **tokens);
void			ft_delete_quotes(char **token, int len, int n, char **tokens);
char			*ft_strjoin(char *s1, char *s2);
void			ft_remove_char(char **token, int i, int len);
int				ft_start_exec(char ***tokens, char ***c_env, char *cmd,
					char *prompt);
int				ft_strcmp(char *s1, char *s2);
int				ft_check_redirect(char ***tokens);
int				ft_count_redir(char **tokens);
char			**ft_init_fd(int *fd, char **tokens, int count_redir);
char			**ft_delete_redir(char **tokens, int count_redir);
int				ft_check_builtins(char **tokens, char ***c_env, int fd);
int				ft_check_bins(char **tokens, char ***c_env, t_fds fds);
int				ft_check_pipe(char ***tokens, char ***c_env, char *cmd,
					char *prompt);
t_p				ft_init_arg(char ***tokens, char ***c_env, char *cmd,
					char *prompt);
void			ft_free_exit(char ***tokens, char ***c_env, char *cmd,
					char *prompt);
void			ft_child_handler(int signum);
int				ft_init_pipes(int *fd1, int *fd2);
int				ft_run_pipe(t_p *arg);
void			ft_run_fork(t_p *arg, char **tokens, int st);
void			ft_next_pipe(int *fd1, int *fd2, int next);
int				ft_write_error(void);
int				ft_echo(char **tokens, int fd);
int				ft_pwd(int fd);
int				ft_first_ispipe(char *cmd);
char			*ft_join_path(char **s1, char *s2);
int				ft_is_start_str(char *str1, char *str2);
int				ft_print_error(char *msg, int code);
int				ft_check_exec(t_bin *param, char **tokens, char **c_env,
					t_fds fds);
int				ft_start_bin(t_bin *param, char **tokens, char **c_env,
					t_fds fds);
int				ft_exit(char **tokens);
int				ft_cd(char **tokens, int fd, char ***env);
int				ft_env(char **tokens, int fd, char **c_env);
int				ft_export(char **tokens, int fd, char ***c_env);
int				ft_unset(char **tokens, int fd, char ***c_env);
void			ft_cd_nullify_preceding_pathname(char **path_splitted, int j);
int				copy_env_vars(char **dst, char *const *src);
void			setup_var(t_var *var, char *var_str);
char			**get_existing_var_record(char **env, char *var_key);
void			update_var(char **existing_var_record, t_var *new_var);
void			ft_extend_env(char ***env, t_var *new_var);
int				is_valid_var_key(char *key);
char			*get_starting_from_symbol(char *s, char c);
void			free_cascade_var(t_var *var);
int				write_single_var_line(int fd, t_var *var, char *var_str);
int				ft_isdigit(int c);
int				is_valid_token_next_to_redirect(char *next_token);
int				ft_check_redirect_input(char ***tokens);
int				ft_check_heredoc(char **tokens, char **c_env);
char			*ft_heredoc_replace_vars(char *cmd, char **c_env);
void			write_tmp_heredoc_file(char *heredoc);
int				is_it_quoted(char *raw_delimiter);
void			make_free(char **var);
char			*construct_root_path(char **path_splitted);
char			*constract_non_root_path(char **path_splitted, int len);
int				is_empty(char **path_splitted, int len);
char			**get_path_splitted(char *const *args, char **env);
char			*construct_abs_path(char **path_splitted, int len);
void			set_oldpwd_var(char **env);
void			set_pwd_var(char **const *env, char *path);
void			err_print_no_such_file_or_dir(char *arg1);
int				check_arg1(char *const *args);
void			write_exit_error_numeric_argument_required(char *first_arg);
void			exit_on_too_many_args(void);
long long int	get_first_arg_number(char *first_arg);
long long int	count_result(const char *first_arg, long long result, int i);
int				handle_no_params(int fd, char **c_env);
int				handle_str_with_equals_sign(char *str, char ***c_env);
char			*rewind_char(char *s, char c);
void			unset_var(char **existing_var_record, char ***env);

#endif