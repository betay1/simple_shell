#include "shell.h"

/**
 * _myhistory - displays the history lis, starting from 0.
 * @info: Structure containing potential arg. to maintain constant function
 *  Return: Always 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	char *i, x;
	int r;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	x = *i;
	*i = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*i = x;
	return (r);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *i;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	if (!*++i)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @node: the alias node
 * Return: Always 0 success, 1 error
 */

int print_alias(list_t *node)
{
	char *i = NULL, *a = NULL;

	if (node)
	{
	i = _strchr(node->str, '=');
	for (a = node->str; a <= i; a++)
		_putchar(*a);
	_putchar('\'');
	_puts(i + 1);
	_puts("'\n");
	return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure contain potential arg.
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	int j = 0;
	char *i = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		i = _strchr(info->argv[j], '=');
		if (i)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
