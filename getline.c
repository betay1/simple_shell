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
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
	free(*buf);
	*buf = NULL;
	signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
		if ((*buf)[r - 1] == '\n')
		{
		(*buf)[r - 1] = '\0';
		x--;
		}
		info->linecount_flag = 1;
		remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);
		{
		*len = r;
		info->cmd_buf = buf;
		}
		}
	}
	return (r);
}

/**
 * get_input - gets line minus newline
 * @info: parameter struct
 * Return: bytes
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
	y = x;
	p = buf + x;

	check_chain(info, buf, &y, x, len);
	while (y < len)
	{
		if (is_chain(info, buf, &y))
		break;
		y++;
	}

		x = y + 1;
		if (x >= len)
		{
		x = len = 0;
		info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf;
	return (r);
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
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
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
	static size_t x, len;
	size_t y;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (x == len)
		x = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	y = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + y : y + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + x, y - x);
	else
		_strncpy(new_p, buf + x, y - x + 1);

	s += y - x;
	x = y;
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
