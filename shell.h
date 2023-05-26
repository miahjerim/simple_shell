#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>



/*convert_number(), chains command, read&write buffers, system getline*/
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct passdata - pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * 
 * @argv: array of strings generated from arg
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @argc: the argument count
 * @line_count: error count
 * @linecount_flag: if on count this line of input
 * @histcount: history line number count
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: history node
	* @cmd_buf_type: CMD_type ||, &&, ;
 * @alias: alias node
	* @fname: program filename
 * @err_num: error code for exit()s
 * @env_changed: on if environ was changed 
 * @arg: string generated from getline
 * @status: return status of the last exec'd command
 * @readfd: fd from which to read line input
 * @path: string path for the current command
 */
typedef struct passdata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
	int env_changed;
	int status;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	char **environ;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
} info_t;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;



#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/*shell_memory.c*/
int freepointer(void **);

/*shell-loop.c*/
int prompt(info_t *, char **);
int get_builtin(info_t *);
void get_command(info_t *);
void fork_command(info_t *);

/*parser.c*/
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c*/
int loophsh(char **);

/*errors.c*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*string0.c*/
int _strlen(char *);
int _strcmp(char *, char *);
char *needle_start(const char *, const char *);
char *_strcat(char *, char *);

/*string1.c*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*shell_exits.c*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/*tokenizer.c*/
char **split_string_0(char *, char *);
char **split_string_1(char *, char);

/*shell_realloc.c*/
char *fill_memory(char *, char, unsigned int);
void free_string(char **);
void *memory_realloc(void *, unsigned int, unsigned int);

/*shell_memory.c*/
int bfree(void **);

/*shell_lists1.c*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


/*errors1.c*/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*builtin0.c*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/*builtin1.c*/
int _myhistory(info_t *);
int _myalias(info_t *);

/*get_line.c*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*shell_lists0.c*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*atoi.c*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/*get_info.c*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/*shell_getenv.c*/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/*shell_vars.c*/
int string_redone(char **, char *);
int chain_test(info_t *, char *, size_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int alias_redone(info_t *);
int vars_redone(info_t *);



/*shell_history.c*/
char *shellhistory_file(info_t *info);
int shellhistory_read(info_t *info);
int shellhistory_write(info_t *info);
int shellhistory_newnumber(info_t *info);
int shellhistory_creatlist(info_t *info, char *buf, int linecount);


#endif