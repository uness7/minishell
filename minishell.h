/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:20 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/11 18:52:55 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCES 1
# define ERROR 0
# define PATH_MAX 1024
# define MAX_INT 2147483647
# define ARENA_SIZE 1048576
# define HEREDOC_SIZE 100
# define ECHO_SIZE 100
# define TARGETS 20
# define ARGS 20
# define BUFFER_SIZE 10
#define BUFFERSIZE 1024
#define READ_END 0
#define WRITE_END 1





typedef enum e_hd_type
{
	DELI = 1,
	CMD = 2,
	ARG = 3,
	NO_CMD = 4
}						t_hd_type;

typedef struct s_hd_arr
{
	t_hd_type	type;
	char		*data;
}						t_hd_arr;

typedef enum e_echo_type
{
	WORD,
	_SPACE,
}						t_echo_type;

typedef struct t_echo_arr
{
	t_echo_type			type;
	char				*data;
}						t_echo_arr;

typedef struct s_env
{
	char				*value;
	char				*name;
	struct s_env		*next;
}						t_env;

typedef struct s_arena
{
	char				*buffer;
	size_t				offset;
	size_t				capacity;
}						t_arena;

typedef struct s_sig_data
{
	t_arena				*arena;
	t_env				*env;
	int					value;
}						t_sig_data;

typedef struct s_stock_split
{
	int					i;
	int					k;
	int					word_len;
	int					words_count;
	int					temp;
	int					start;
	char				**result;
}						t_stock_split;

typedef struct s_stock
{
	int					*status;
	char				**argv;
	char				**envp;
	t_arena				*arena;
	t_env				*env;
}						t_stock;

typedef enum e_cmd_type
{
	SIMPLE,
	R_OUT,
	R_IN,
	R_APPEND,
	R_HEREDOC
}						t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type			type;
	char				**av;
	char				*target;
	char				*delimeter;
}						t_cmd;

typedef struct s_sk_2
{
	char				**result;
	int					temp;
	int					start;
}						t_sk_2;

typedef struct s_sk_1
{
	int					*fd_flag;
	int					*fd;
	char				**envp;
	int					num_cmds;
	t_cmd				**cmds;
	t_stock				*stock;

}						t_sk_1;

typedef struct s_redir_heredoc
{
	t_hd_arr			**av;
}						t_redir_heredoc;

typedef struct s_redir_cmd
{
	char				**av;
	char				*target;
}						t_redir_cmd;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_ENV_VAR
}						t_token_type;

typedef struct s_node
{
	char				*data;
	t_token_type		type;
	struct s_node		*next;
}						t_node;

typedef struct s_list
{
	t_node				*head;
}						t_list;

/* Abstract Syntac Tree */
typedef enum e_node_type
{
	NODE_COMMAND = 1,
	NODE_ARGUMENT = 2,
	NODE_PIPELINE,
	NODE_REDIRECTION_OUT,
	NODE_REDIRECTION_IN,
	NODE_REDIRECTION_APPEND,
	NODE_REDIRECTION_HEREDOC,
}						t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				*data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;






///////////////      Programs        /////////////////////

typedef struct s_program
{
	t_node_type	type;
	int	fd_out;
	int	fd_in;
	int	f_heredoc;
	char	**args;
	char	*cmd;
}						t_program;


t_program       *extract_program_command(t_ast_node *root);
t_program       *extract_program_redir_in(t_ast_node *root);
t_program       *extract_program_redir_out_append(t_ast_node *root, int a);
t_program       **extract_programs(t_ast_node *root, int programs_count);
t_program       **extract_programs_pipeline(t_ast_node *root, \
		t_program **programs, int programs_count, int *i);
void		run_programs(t_program **programs, char **envp, t_arena *arena);

///////////////////////////////////////////////////////////////////////////












// builtins
void					ft_cd(t_arena *arena, char *path, t_env *env);
char					*get_dir(t_arena *arena);
void					ft_pwd(t_arena *arena);

// linkedList.c file
t_node					*create_node_list(t_arena *arena, char *data,
							t_token_type type);
void					init_list(t_list *list);
void					append(t_arena *arena, t_list *list, char *data,
							t_token_type type);
void					print_list(t_list *list);

// lexer.c file
t_token_type			get_char_type(char c);
t_list					*tokenize(t_arena *arena, const char *s);
void					handle_special_chars(t_arena *arena, const char **s,
							t_list **list);

// parser.c file
t_ast_node				*parse(t_arena *arena, t_list *stream);
void					parse_command(t_arena *arena, t_ast_node **root,
							char *data, int is_last);
void					parse_pipeline(t_arena *arena, t_ast_node **root,
							char *data);
t_ast_node				*find_mostleft_cmd(t_ast_node **root);
void					parse_redir_heredoc(t_arena *arena, t_ast_node **root,
							char *data);

// trees.c file
t_ast_node				*create_node_tree(t_arena *arena, t_node_type type,
							char *data);
void					print_tree(t_ast_node *root);

// executor.c file
char					**build_command(t_arena *arena, t_ast_node *root);
int						execute(t_stock *stock, char *cmd_path, char **av);
int						find_number_nodes(t_ast_node *root);

// utils.c files
char					*find_paths(char **envp);
char					*find_cmd(t_arena *arena, char **paths, char *cmd);
char					*ft_strjoin(t_arena *arena, char *s1, char *s2);
char					**ft_strtok(t_arena *arena, char *s);
char					*ft_strtok_2(char *str, char *delim);
int						ft_strncmp(char *s1, char *s2, unsigned int n);
size_t					ft_strlen(char *str);
char					*ft_strchr(char *str, int c);
int						ft_atoi(const char *str);
long int				ft_atol(char *str);
int						is_num(char *str);

// executor_redir_out.c file
int						execute_redir_out(t_stock *stock, char *cmd_path,
							char *target, char **av);
t_redir_cmd				*build_cmd_redir_out(t_arena *arena, t_ast_node *root);

// executor_redir_append.c file
int						execute_redir_append(t_stock *stock, char *cmd_path,
							char *target, char **av);

t_redir_cmd				*build_cmd_redir_append(t_arena *arena,
							t_ast_node *root);

// executor_redir_heredoc.c file:
int						execute_redir_heredoc(t_stock *stock, char *cmd_path,
							char **input, char **av);

t_redir_heredoc			*build_cmd_redir_heredoc(t_arena *arena,
							t_ast_node *root);
char					**get_input(t_arena *arena, char *eof);

void					malloc_err(void);
void					ft_putstr_fd(char *str, int fd);
void					free_array(char **s);

// execuotr_redir_in.c file :
int						execute_redir_in(t_stock *stock, char *cmd_path,
							char *target, char **av);

t_redir_cmd				*build_cmd_redir_in(t_arena *arena, t_ast_node *root);

// pipelines.c file :
int						execute_pipeline(t_stock *stock, t_cmd **commands,
							int *i, int *fd);
void					extract_commands(t_arena *arena, t_ast_node *tree,
							t_cmd ***commands, int *num_commands);
void					inverse_commands_order(t_arena *arena, t_cmd **cmd);
void					add_to_array(t_cmd **a1, char **a2);

void					execute_tree(t_ast_node *tree, char **envp);
void					_execute_pipeline(t_ast_node *tree, char **envp);
int						_execute_redir_heredoc(t_stock *stock, int fd[2],
							t_cmd *cmd);
void					close_fd(int fd[2]);
void					exchange_fd(int fd_prev[2], int fd_curr[2]);

/* Rest of pipelines files */
void					run_r_out(t_stock *stock, t_sk_1 *sk, char *path,
							t_cmd *cmd);
void					run_r_in(t_stock *stock, t_sk_1 *sk, char *path,
							t_cmd *cmd);
void					extract_subcommand_simple(t_arena *arena,
							t_ast_node *node, t_cmd ***commands,
							int *num_commands);
void					extract_subcommand_r_out(t_arena *arena,
							t_ast_node *node, t_cmd ***commands,
							int *num_commands);
void					extract_subcommand_r_in(t_arena *arena,
							t_ast_node *node, t_cmd ***commands,
							int *num_commands);
void					extract_subcommand_r_append(t_arena *arena,
							t_ast_node *node, t_cmd ***commands,
							int *num_commands);
void					extract_subcommand_r_heredoc(t_arena *arena,
							t_ast_node *node, t_cmd ***commands,
							int *num_commands);

/* Minishell */
void					run_simple_command(t_stock *stock, t_ast_node *tree,
							char *input);
void					run_redir_out_command(t_stock *stock, char *input,
							t_ast_node *tree);
void					run_redir_append_command(t_stock *stock, char *input,
							t_ast_node *tree);
void					run_redir_in_command(t_stock *stock, t_ast_node *tree);
void					run_redir_heredoc_command(t_stock *stock,
							t_ast_node *tree);
int						run_expr(t_stock *stock, char **av, char *input);

void					run_pipeline_command(t_stock *stock, t_ast_node *tree);
char					*join_args(t_arena *arena, char **args);

/* Built-ins */
bool					_isbuiltin(t_arena *arena, char *input);
void					_runbuiltins(t_stock *stock, char *input);
char					*trim_space(char *str);
char					*trim_quotes(t_arena *arena, char *str);
void					ft_exit(t_arena *arena, char *argv, int *status);
int						ft_echo(t_arena *arena, char *argv);
void					append_env_node(t_arena *arena, t_env **head,
							char *name, char *value);
void					free_env_list(t_env *head);
t_env					*ft_env(t_arena *arena, char **env);
void					print_env(t_env *list);
t_env					*find_env_var(t_env **head, char *key);
void					update_env_var(t_arena *arena, t_env *env_var,
							char *name, char *value);
void					add_or_update_env(t_arena *arena, t_env **head,
							char *name, char *value);
void					unset(t_env **list, char *value);
char					**custom_split(char *input_string, char delimiter);
char					**ft_str_copy(t_arena *arena, char **envp);
void					custom_echo(t_arena *arena, char *input, t_env *envp);
void					custom_unset(char *input, t_env *env);
void					custom_export(t_stock *stock, char *input);
void					custom_cd(t_arena *arena, char *input, t_env *env);
void					custom_exit(char *input, int *status);
void					search_value(char **envp_cp, char **arg);
void					check_n_arg(int *n_flag, char **args);
void					handle_n_arg(char *args);
char					**convert_list_array(t_arena *arena, t_list *list);
void					check_n_option(char ***args, char *str, int *all_n);
char					**allocate_memory_echo(t_arena *arena);

/* Signals */
void					handle_sig(int sig);
void					handle_sig2(int sig);
void					init_signal(void);

/* Errors */
void					pipe_err(void);
void					free_array(char **s);
void					fork_err(void);
void					execve_err(t_arena *arena, t_env *env);
void					open_err(void);

/* LIBFT FUNCTIONS */
char					*ft_strdup(t_arena *arena, char *s);
int						ft_strcmp(char *s1, char *s2);
int						ft_strncmp(char *s1, char *s2, unsigned int n);
char					*ft_strstr(char *haystack, char *needle);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src, size_t n);
int						ft_isspace(int c);

/* ft_split helper functions */
char					**ft_split(t_arena *arena, const char *s, char delim);

/* Input Validation */
bool					is_input_valid(char *input);
bool					has_valid_heredoc(char *s);
/* multiple redir heredoc */
bool					has_multiple_redir_heredoc(char *input);
void					run_multiple_redir_out(t_arena *arena, char *input);
char					**extract_files(t_arena *arena, char *input);
char					**extract_args(t_arena *arena, char *input);
bool					has_multiple_redir_out(char *command);
bool					has_multiple_redir_in(char *command);
bool					has_multiple_redir_append(char *command);
bool					has_multiple_delimeters(char *command);
void					_run_redir_out_command(t_stock *stock,
							t_redir_cmd *redir, char *input);
void					_run_redir_out_command2(t_stock *stock,
							t_redir_cmd *redir, char *cmd);

void					_run_redir_append_command(t_stock *stock,
							t_redir_cmd *redir, char *input);
void					_run_redir_append_command2(t_stock *stock,
							t_redir_cmd *redir, char *cmd);

void					_run_redir_heredoc_command(t_stock *stock,
							t_redir_heredoc *rh, char *input);
void					_run_redir_heredoc_command2(t_stock *stock,
							t_redir_heredoc *rh, char *cmd);

/* Input Validation */

bool					check_invalid_combinations(t_arena *arena, t_list *list,
							t_env *env);
bool					check1(t_node *temp);
bool					check2(t_node *temp);
bool					check3(t_node *temp);
bool					check4(t_node *temp);
bool					check5(t_node *temp);
bool					has_logical_ops(char *s);
bool					has_double_unclosed_quotes(char *s);
bool					has_single_unclosed_quotes(char *s);
bool					is_input_valid(char *s);
bool					is_input_valid2(char *s);

/* itoa */
char					*ft_itoa(t_arena *arena, int n);

/* Utils */
char					*ft_strndup(t_arena *arena, const char *str, size_t n);
char					*ft_strcat(char *s1, char *s2);

/* Arena Functions */
void					arena_init(t_arena *arena, size_t capacity);
void					free_arena(t_arena *arena);
void					*arena_alloc(t_arena *arena, size_t size);

void					expand_var(t_stock *stock, char *input);
//void					heredoc(t_arena *arena, char *input);
void					expand_env_var_in_pipes(t_cmd **commands,
							t_stock *stock);
void					expand_env_var_heredoc(t_redir_heredoc *rh,
							t_stock *stock);
char					*trim_single_quotes(t_arena *arena, char *str);

char					**env_list_arr(t_arena *arena, t_env *temp, int size);
int						env_list_size(t_env *list);
int						array_size(char **arr);
void					close_exit(void);
void					handle_sig_heredoc(int sig);
void					err(void);
char					**get_input_helper(t_arena *arena, int i, int count,
							char *eof);
void					copy_result(t_arena *arena, char *input, char ***result,
							int *count);
void					swap(char **av);

/* Expander */
char					*expand_variables(t_stock *stock, const char *input);

/* Tools */
char					**ft_split_2(const char *str);
t_echo_arr				**split(t_arena *arena, char *input);
int					is_space(char c);
/* gnl */

char	*get_next_line(int fd);

#endif
