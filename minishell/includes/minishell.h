/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:55:40 by ychng             #+#    #+#             */
/*   Updated: 2024/04/01 23:24:30 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "sys_headers.h"
# include "libft.h"

typedef struct s_subtokennode
{
	char					*subtoken;
	struct s_subtokennode	*next;
	struct s_subtokennode	*prev;
}	t_subtokennode;

typedef struct s_subtokenlist
{
	t_subtokennode	*head;
	t_subtokennode	*tail;
}	t_subtokenlist;

typedef struct s_tokennode
{
	t_subtokenlist		*subtokenlist;
	struct s_tokennode	*next;
	struct s_tokennode	*prev;
}	t_tokennode;

typedef struct s_tokenlist
{
	t_tokennode	*head;
	t_tokennode	*tail;
}	t_tokenlist;

typedef struct s_treenode
{
	t_tokennode			*token;
	struct s_treenode	*left;
	struct s_treenode	*right;
	struct s_treenode	*next;
}	t_treenode;

// character_check_1.c
bool			is_backslash(char c);
bool			is_singlequote(char c);
bool			is_double_quote(char c);
bool			is_quote(char c);
bool			is_delim(char c, char *delim);

// character_check_2.c
bool			is_underscore(char c);
bool			is_hash(char c);
bool			is_dollar_sign(char c);
bool			is_asterisk(char c);
bool			is_ampersand(char c);

// character_check_3.c
bool			is_question_mark(char c);
bool			is_exclamation(char c);
bool			is_number(char c);
bool			is_uppercase(char c);
bool			is_lowercase(char c);

// character_check_4.c
bool			is_tilde(char c);
bool			is_newline(char c);
bool			is_escapable(char c);
bool			is_space(char c);
bool			is_sign(char c);

// character_check_5.c
bool			is_equal(char c);
bool			is_leftbracket(char c);
bool			is_rightbracket(char c);
bool			is_bracket(char c);
bool			is_pipe(char c);

// character_check_6.c
bool			is_forward_slash(char c);

// operator_check_1.c
bool			is_logicalop(char *str);
bool			is_logicalop_n(char *str);
bool			is_redirection(char *str);
bool			is_redirection_n(char *str);
bool			is_heredoc(char *str);

// operator_check_2.c
bool			is_append(char *str);
bool			is_output(char *str);
bool			is_infile(char *str);

// builtins/blt_echo_utils.c
bool			is_n_options(char *subtoken);
t_subtokennode	*find_first_non_option(t_subtokennode *args);

// builtins/blt_echo.c
int				blt_echo(t_subtokennode *args);

// builtins/blt_cd_utils_1.c
void			handle_oldpwd(char **envp);
void			handle_pwd(char **envp);
void			move_to_home_directory(void);
void			move_to_parent_directory(void);

// builtins/blt_cd_utils_2.c
char			*update_oldpwd(void);
char			*update_pwd(void);

// builtins/blt_cd.c
int				blt_cd(char **envp, t_subtokennode *args);

// builtins/blt_pwd.c
int				blt_pwd(void);

// builtins/blt_export_utils_1.c
int				count_valid_args(char **envp, t_subtokennode *args);
void			add_valid_args(char **envp, t_subtokennode *args);
void			pad_envp_entry(char **envp);
void			trim_entry_pad(char **envp);
void			print_export_envp(char **envp);

// builtins/blt_export_utils_2.c
bool			entry_has_valid_name(char *args);
bool			is_not_duplicate(char **envp, char *args);
void			handle_duplicate(char **envp, char *args);

// builtins/blt_export_utils_3.c
int				get_max_env_name_len(char **envp);
char			*pad_env_name(char *entry, int maxlen);
char			*trim_env_name_pad(char *entry);

// builtins/blt_export_utils_4.c
void			radix_sort(char **envp);

// builtins/blt_export.c
int				blt_export(char ***envp, t_subtokennode *args);

// builtins/blt_unset.c
int				blt_unset(char **envp, t_subtokennode *args);

// builtins/blt_env.c
int				blt_env(char **envp);

// builtins/blt_exit_utils.c
bool			contain_only_digits(char *first_arg);
int				normalize_exit_code(char *first_arg);
void			handle_numeric_exit(char *first_arg, char *dup_subtoken);
void			handle_non_numeric_exit(char *dup_subtoken);

// builtins/blt_exit.c
int				blt_exit(t_subtokennode *args);

// double_array_utils.c
int				count_2d_array_items(char **double_array);
char			**clone_double_array(char **double_array);
void			free_double_array(char **double_array);

// clone_envp_with_special.c
char			**clone_envp_with_special(char **envp);

// quote_handling.c
void			toggle_inquote(char c, bool *inquote, char *quote_type);

// get_next_token_utils.c
int				len_of_operator(char *remaining_input);
bool			is_bracket_or_logical_operator(char *remaining_input, \
					bool withbracket);

// get_next_token.c
char			*get_next_token(char *input, bool withbracket);

// get_next_subtoken_utils.c
int				len_of_redirection(char *subtoken);
bool			is_space_or_redirection(char *subtoken);

// get_next_subtoken.c
char			*get_next_subtoken(char *token);

// custom_strtok.c
char			*custom_strtok(char *input, char *delim);

// env_check.c
bool			is_special_env_name(char c);
bool			is_valid_env_name(char c);
bool			is_env_var(char *remaining_input);

// get_next_env.c
char			*get_next_env(char *subtoken);

// string_utils.c
char			*custom_strjoin(char *s1, char *s2);

// read_inputline_utils_1.c
bool			has_logicaloperr(char *token, int *openlogicalops);
bool			has_bracketerr(char *token, int *openbrackets);
bool			has_redirerr(char *token, int *openredir);
bool			has_noerror(char *input);

// read_inputline_utils_2.c
int				redirlen(char *token);
bool			is_notvalidname(char *token);

// read_inputline_utils_3.c
bool			has_openquotes(char *input);
bool			has_openbrackets(char *input);
bool			has_openlogicalops(char *input);
bool			has_openblock(char *input);

// read_inputline_utils_4.c
bool			is_validpos(char *start, char *input);
int				update_open_count(char c);
int				set_inoperator_true(bool *inoperator);

// read_inputline_utils_5.c
int				dup_stdoutfd(char *input);
int				dup_nullfd(char *input);
char			*trim_errorpart(char *input);

// read_inputline_utils_6.c
int				validlen(char *token, int *openbrackets);
int				validlenredir(char *token);
char			*extract_heredoc(char *input, int joinedlen);

// read_inputline_utils_7.c
char			*format_joininput(char *joininput);

// read_inputline_helper.c
char			*closequotes(char *input);
char			*closebrackets(char *input);
char			*closelogicalops(char *input);

// read_inputline.c
char			*read_inputline(void);

// expand_env_utils_1.c
int				count_len_until_env(char *subtoken, char *env);
char			*get_env_value(char *env, char **envp);
int				count_env_value_len(char *env, char **envp);
int				skip_env(char *env);
char			*append_env_value(char *result, char *env, char **envp);

// expand_env_utils_2.c
bool			is_valid_syntax(char *envp);

// expand_env.c
char			*expand_env(char *subtoken, char **envp);

// expand_tilde_utils_1.c
int				count_valid_key_name(char *subtoken);
char			*extract_until_delim(char *user, char *delim);
char			*find_user_directory(char *user);

// expand_tilde_utils_2.c
DIR				*open_users_directory(void);
char			*find_home_directory(char *entry_name, char *user);
char			*extract_key(char *subtoken);

// expand_tilde_helper.c
char			*join_expanded_tilde_with_remains(char *directory, \
												char *remains);
char			*join_key_with_value(char *value, char *subtoken);

// expand_tilde.c
char			*expand_tilde(char *subtoken);

// get_next_line_utils.c
bool			contains_newline(char *remaining_line);
int				read_and_check(int fd, char *buffer, int buffer_size);

// get_next_line.c
char			*get_next_line(int fd);

// expand_escaped_utils.c
bool			should_escape(char quote_type, char *subtoken);

// expand_escaped.c
char			*expand_escaped(char *subtoken);

// subtokenlist_utils_1.c
t_subtokennode	*new_subtokennode(char *subtoken);
t_subtokenlist	*create_subtokenlist(void);
t_subtokennode	*pop_subtokenlist_head(t_subtokenlist *subtokenlist);
t_subtokennode	*pop_subtokenlist_tail(t_subtokenlist *subtokenlist);
void			link_subtokenlist(t_subtokennode *subtokennode, \
								t_subtokenlist *subtokenlist);

// subtokenlist_utils_2.c
int				count_subtokenlist(t_subtokenlist *subtokenlist);

// tokenlist_utils.c
t_tokennode		*create_tokennode(t_subtokenlist *subtokenlist);
t_tokenlist		*create_tokenlist(void);
t_tokennode		*pop_tokenlist_head(t_tokenlist *tokenlist);
t_tokennode		*pop_tokenlist_tail(t_tokenlist *tokenlist);
void			link_tokenlist(t_tokennode *tokennode, \
								t_tokenlist *tokenlist);

// get_tokenlist_utils.c
char			*expand_subtoken(char *subtoken, bool expand_heredoc, \
									char **envp);

// get_tokenlist.c
t_tokenlist		*get_tokenlist(char *input, char **envp);

// build_tree_utils_1.c
char			*currsubtok_in(t_tokenlist *tokenlist);
t_treenode		*pop_treenode_from(t_treenode **list);
t_treenode		*new_treenode(t_tokennode *tokennode);
void			push_(t_treenode *cmdnode, t_treenode **cmdlist);

// build_tree_utils_2.c
t_treenode		*getlastnode(t_treenode *cmdlist);

// build_tree.c
t_treenode		*build_tree(t_tokenlist *tokenlist);

// evaluate_heredocs.
void			evaluate_heredocs(t_treenode *root);

// evaluate_tree_utils_1.c
void			exec_cmd(char ***envp, int prev_pipefd[], \
						t_subtokenlist **currcmd, bool is_lastcmd);
void			wait_for_forks(char **envp);
int				get_exitstatus(char **envp);

// evaluate_tree_utils_2.c
void			handle_pipecmd(char ***envp, int pipefd[], int prev_pipefd[], \
							t_subtokenlist **currcmd);
void			handle_lastcmd(char ***envp, int prev_pipefd[], \
							t_subtokenlist **currcmd);

// evaluate_tree_utils_3.c
pid_t			create_fork(void);

// evaluate_tree_utils_4.c
t_subtokenlist	*extract_redirection(t_subtokenlist **currcmd);
int				get_infilefd(t_subtokenlist *redirlist);
int				get_outfilefd(t_subtokenlist *redirlist);

// evaluate_tree_utils_5.c
int				run_cmd(char ***envp, t_subtokenlist *currcmd);
void			update_exit_status(char **envp, int exit_status);
bool			is_builtins(t_subtokenlist *currcmd);

// evaluate_tree_utils_6.c
int				run_execve(char **envp, t_subtokenlist *currcmd);

// evaluate_tree.c
bool			evaluate_tree(t_treenode *root, char ***envp);

// free_list.c
void			free_subtokennode(t_subtokennode *subtokennode);
void			free_subtokenlist(t_subtokenlist *subtokenlist);
void			free_tokennode(t_tokennode *tokennode);
void			free_tokenlist(t_tokenlist *tokenlist);

#endif
