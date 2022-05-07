/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:39:58 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 18:17:42 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	t_list	*list_cmd;
	char	**env_p;
	int		env_status;
}			t_data;

typedef struct s_full
{
	char	**full_cmd;
	char	*full_path;
	int		in_file;
	int		out_file;
}			t_full;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11
};

char	*shell_readline(t_data *prompt, char *str);
void	*shell_here_fd(t_data *prompt, int fd[2], int auxfd[2]);
int		shell_builtin(t_data *prompt, t_list *cmd, int *is_exit, int n);
int		is_builtin(t_full *n);
int		shell_cd(t_data *prompt);
int		shell_pwd(void);
int		shell_echo(t_list *cmd);
int		shell_export(t_data *prompt);
int		shell_unset(t_data *prompt);
int		shell_exit(t_list *cmd, int *is_exit);
void	*check_args(char *out, t_data *p);
char	**ft_cmd_trim(char const *s, char *set);
char	**ft_cmd_subsplit(char const *s, char *set);
char	*ft_strtrim_all(char const *str1, int squote, int dquote);
t_list	*fill_nodes(t_data *prompt, char **args, int i);
int		get_fd(t_data *prompt, int oldfd, char *path, int flags[2]);
t_full	*get_outfile1(t_data *prompt, t_full *node, char **args, int *t);
t_full	*get_outfile2(t_data *prompt, t_full *node, char **args, int *t);
t_full	*get_infile1(t_data *prompt, t_full *node, char **args, int *t);
t_full	*get_infile2(t_data *prompt, t_full *node, char **args, int *t);
void	*exec_cmd(t_data *prompt, t_list *cmd);
void	child_builtin(t_data *prompt, t_full *g, int r, t_list *cmd);
void	exec_cust(char ***out, char *full, char *args, char **envp);
int		exec_builtin(t_data *prompt, int (*func)(t_data *));
void	get_cmd(t_data *prompt, t_list *start, char **split_path, char *path);
char	*expand_vars(char *str, int t, int quotes[2], t_data *prompt);
char	*expand_path(char *str, int t, int quotes[2], char *var);
int		get_here_doc(t_data *prompt, char *str[2], size_t len, char *aux[2]);
void	*shell_perror(t_data *prompt, int err, char *param);
char	*mini_getenv(char	*var, char **envp, int t);
char	**mini_setenv(char *var, char *value, char **envp, int t);
char	*shell_getprompt(t_data prompt);
void	free_content(void *content);
void	handle_sigint(int sig);
void	handle_sigint_child(int sig);
void	handle_sigquit(int sig);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putendl_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
char	**ft_dup_matrix(char **m);
void	ft_free_matrix(char ***m);
int		ft_putmatrix_fd(char **m, int fd);
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	**ft_extend_matrix(char **in, char *newstr);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newnode);
t_list	*ft_lstnew(void *content);
int		ft_strchars_i(const char *s, char *set);
int		ft_isspace(char c);
int		ft_strchr_i(const char *s, int c);
int		ft_matrixlen(char **m);
char	**ft_matrix_replace_in(char ***big, char **small, int n);
int		ft_lstsize(t_list *lst);
char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
int		gnl_strchr_i(const char *s, int c);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_strlcat(char *dst, const char *src, size_t size);
char	*gnl_shrink_buffer(char *buf, char *line);
char	*gnl_expand_buffer(char *buf, int fd);
char	*gnl_newread(int fd);

#endif
