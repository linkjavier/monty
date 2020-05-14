#include "monty.h"
int number;

/**
 * execute_opcode - read, open and execute.
 * @argv: arguments
 */

void execute_opcode(char **argv)
{
	FILE *fp = NULL;
	char str[1000];
	char *filename = argv[1], *line = NULL, *token = NULL;
	unsigned int line_number = 1;
	void (*funct)(stack_t **stack, unsigned int line_number);
	stack_t *top = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL)
		open_error(argv);

	while ((line = fgets(str, 1000, fp)) != NULL)
	{
		token = strtok(line, " \t\n\r");
		if (token == NULL)
			continue;
		strcpy(str, token);
		if (is_hash(token, line_number) == 1)
			continue;
		if (strcmp(token, "push") == 0)
		{
			token = strtok(NULL, " \t\n\r");
			if (token == NULL || is_number(token) == -1)
				not_int_error(line_number);
			number = atoi(token);
			funct = get_op_code(str, line_number);
			funct(&top, line_number);
		}
		else
		{
			funct = get_op_code(token, line_number);
			funct(&top, line_number);
		}
		line_number++;
	}
	_free_stack(top);
	fclose(fp);
}
