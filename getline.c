#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*len)
	{
	free(*buf);
	*buf = NULL;
	signal(SIGINT, sigintHandler);

#if USE_GETLINE
		x = getline(buf, &len_p, stdin);
#else
		x = _getline(info, buf, &len_p);
#endif
		if (x > 0)
		{
		if ((*buf)[x - 1] == '\n')
		{
		(*buf)[x - 1] = '\0';
		x--;
		}
		info->linecount_flag = 1;
		remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);
		{
		*len = x;
		info->cmd_buf = buf;
		}
		}
	}
	return (x);
}

/**
 * get_input - gets line minus newline
 * @info: parameter struct
 * Return: bytes
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t x = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1)
		return (-1);
	if (len)
	{
	j = i;
	p = buf + i;

	check_chain(info, buf, &j, i, len);
	while (j < len)
	{	
		if (is_chain(info, buf, &j))
		break;
		j++;
	}

		i = j + 1;
		if (i >= len)
		{
		i = len = 0;
		info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf;
	return (x);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * _getline - next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buff if NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t x = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + j : j + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, j - i);
	else
		_strncpy(new_p, buf + i, j - i + 1);

	s += j - i;
	i = j;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl
 * @sig_num: signal num
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
