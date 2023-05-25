#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include "ansi.h"
#include "get.h"

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CMD_PIPE 4

#define STARTUP_FILECONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".shell_history"
#define HIST_max 4096
#define DOC_FD -2
#define START_ARRAY_SIZE 10
#define START_FILE ".shellrc"

extern char **environ;

/**
 * struct lststr - singly linked list
 * @numberF: number field
 * @str: string
 * @nxt: next node
 */
typedef struct lststr
{
	int numberF;
	char *str;
	struct lststr *nxt;
} list_t;

/**
 * struct pinfo - contains pseudo-arguements to pass into a function
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: the string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecountF: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @Hcount: the history line number count
 * @left_redirect_from_fd: the fd to left redirect from
 * @left_append: true if hdoc
 * @right_redirect_from_fd: fd right redirecting from (default 1)
 * @right_redirect_to_fd: fd right redirecting to
 * @right_append: true if right stream appends
 * @hdoc: value of HDOC delimeter
 * @hdoc_txt: accumulated HDOC lines
 * @hdoc_cmd: the command to pipe HDOC line
 * @help: help flags
 * @pipefd: fd pipe for interprocess communication | pipe
 * @startup_fd: fd of startup file or -1
 * @dup_stdin: saved duplicate of stdin for restoration after redirect
 * @dup_stdout: saved duplicate of stdout for restoration after redirect
 */

typedef struct pinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecountF;
	char *fname;
	list_t *history;
	list_t *env;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int Hcount;
	int left_redirect_from_fd;
	int left_append;
	int right_redirect_from_fd;
	int right_redirect_to_fd;
	int right_append;
	char *hdoc;
	char *hdoc_txt;
	char *hdoc_cmd;
	char *help;
	int pipefd[3];
	int startup_fd;
	int dup_stdin;
	int dup_stdout;

} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0, -1, 0, 1, -1, 0, NULL, NULL, NULL, NULL, {0}, -1, 0, 0}

/**
 * struct bltin - contains a builtin string and function
 * @typeB: command flag
 * @function: the function
 */
typedef struct bltin
{
	char *typeB;
	int (*function)(info_t *);
} B_table;

/*shell.c*/

int shell(info_t *, char **);
int find_bltin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);
void handle_redirects(info_t *info);

/*path.c*/

int is_command(info_t *, char *);
char *dupl_char(char *, int, int);
char *find_path(info_t *, char *, char *);

/*help1.c*/
void help1(void);
void help1_cd(info_t *);
void help1_exit(info_t *);
void help1_help(info_t *);
void help1_hist(info_t *);

/*help2.c*/
void help2_alias(info_t *);
void help2_echo(info_t *);
void help2_pwd(info_t *);

/*string_functions_error.c*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int *fd);
int _putsfd(char *str, int fd);

/*str_functions.c*/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*str_fucntion3.c*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strchlast(char *c, char s);

/*str_function2.c*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*str_function4.c*/
char **strtow0(char *, char *);
char **strtow1(char *, char);

/*memo_func.c*/
char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/*more_func.c*/
int intractive(info_t *);
int is_deli(char, char *);
int isal(int);
int _atoi(char *);

/*more_func2.c*/
int _errato(char *);
int print_d(int, int);
char *convert_num(long int, int, int);
void rmv_comment(char *);

/*bltin_emul.c*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
char *helpf_check(info_t *, char **);

/*bltin_emul2.c*/
int _myhist(info_t *);
int _myalias(info_t *);

/*getline.c*/
ssize_t get_inp(info_t *);
int _getline(info_t *, char **, size_t *);
void siginthandle(int);

/*info.c*/
void clear_info(info_t *);
int set_info(info_t *inf, char **av);
void free_info(info_t *, int);
void print_info(info_t *inf);

/*env.c*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int pop_env_lst(info_t *);

/*env2.c*/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
void print_prompt(info_t *);

/*file_func.c*/
char *get_historyf(info_t *inf);
int write_hist(info_t *inf);
int read_hist(info_t *inf);
int build_hist_lst(info_t *inf, char *buf, int linecount);
int renum_hist(info_t *inf);

/*lststr.c*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_lst_string(const list_t *);
int del_node_ind(list_t **, unsigned int);
void free_lst(list_t **);

/*lststr2.c*/
size_t lst_len(const list_t *);
char **lst_str(list_t *);
size_t print_lst(const list_t *);
list_t *node_start(list_t *, char *, char);
ssize_t node_ind(list_t *, list_t *);

/*chains.c*/
int chain(info_t *, char *, size_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int repl_alias(info_t *);
int repl_var(info_t *);
int repl_str(char **, char *);

/*redir.c*/
void parse_redir_left(info_t *inf);
void parse_redir_right(info_t *inf);
int open_redir(info_t *inf, char *fle, int lft);
size_t parse_hdoc(info_t *inf, char **buf, size_t s);
void rest_stdfd(info_t *inf);

/*pipefd.c*/
void open_pipefd(info_t *inf);

/*err.c*/
void print_err(info_t *, char *);
void print_err_noarg(info_t *inf, char *str);

/*startup_fd.c*/
int open_fle(info_t *inf, char *nom, int silence);
void read_startup_fd(info_t *inf);

/*date.c*/
char *date(void);
char *time(int);
char *day(int);
char *month(int);

#endif
