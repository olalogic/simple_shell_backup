#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int start_shell(char **environ, char *exec_name);

void print_prompt(void);

int do_shell_eof_or_newline(char *input, int bytes_read);


#define NORM_DELIMS " \t\a\r\n"
#define PATH_DELIMS ":"

#define NO_SEPARATOR '\0'
#define AND_LOGIC_SEP '&'
#define OR_LOGIC_SEP '|'
#define COMMAND_SEP ';'

/**
 * struct command_s - Structure of each node
 *
 * @prev_valid: Check if previous command
 * was successful
 *
 * @separator: Used for character that
 * that separates each command
 *
 * @command: Points to the first char
 * in the stream
 *
 * @next: Address of next node
 *
 */
typedef struct command_s
{
	int prev_valid;

	char separator;
	char **command;
	struct command_s *next;
} command_t;

/**
 * struct queue_s - Structure of queue
 *
 * @front: Pointer to the first node
 *
 * @rear: Pointer to the front+1 node
 *
 */

typedef struct queue_s
{
	command_t *front, *rear;
} queue_t;




#define LOGIC_DELIMS "&|;"
queue_t *parse_string(char *str);
int is_logic(char *token);
char **get_command_tokens(char **raw_tokens, int beg_ind, int end_ind);

/**
 * struct history_s - Structure of history queue
 *
 * @command: Holds the command from getline()
 *
 * @priority_number: Holds the number coorelated
 * to the command input order
 *
 * @next: Pointer to the next node
 *
 */

typedef struct history_s
{
	char *command;

	int priority_number;
	struct history_s *next;
} history_t;



/**
 * struct his_q_s - Structure of queue
 *
 * @front: Pointer to the first node
 *
 * @rear: Pointer to the front+1 node
 *
 */

typedef struct his_q_s
{
	history_t *front, *rear;
} his_q_t;



his_q_t *get_history();

his_q_t *create_h_queue();
history_t *h_dequeue(his_q_t *q);

int execute_commands(his_q_t *his_q, queue_t *command_q
		, char *envp[], char *exec_name);
int can_execute(command_t *command);
int is_custom_command(char *token);

int execute_normal_command(command_t *command, char *envp[], char *);
int execute_custom_command(command_t *, char **, his_q_t *, queue_t *);
int h_enqueue(his_q_t *q, char *command);
void write_h_queue(his_q_t *q, int fd);
command_t *create_command(char separator, char **command);
void free_command_queue(queue_t *q);
void free_token_list(char **tokens);
void free_command(command_t *command);

int register_signal_handlers(void);
void signal_handler(int sig_no);


void print_no_file_error(char *exec_name);
void print_perm_denied(char *exec_name);
void print_signal_reg_error(void);
void print_newline(void);

#endif
