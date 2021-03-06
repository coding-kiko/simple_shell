#include "holberton.h"

/**
 * count_dirs - entry point
 * @path: path
 * Count arranca en 3 porque un array es para PATH otro para nulo y carpeta
 * Return: 0 succes
 */

int count_dirs(char *path)
{
	int count = 3, i = 0;

	for (i = 0 ; path[i] != '\0' ; i++)
	{
		if (path[i] == ':')
			count++;
	}
	return (count);
}

/**
 * count_sep - entry point
 * @sep: number of arguments passed
 * @str: string to separate
 * separador universal
 * Return: cantidad de separadores
 */

int count_sep(char *str, char sep)
{
	int count = 0, i = 0;

	for (i = 0 ; str[i] != '\0' ; i++)
	{
		if (str[i] == sep)
			count++;
	}
	return (count);
}

/**
 * parser - entry point
 * @str: string que entra al command line de hsh
 * lo separa por espacios y por \n
 * Return: array de string metidos al command line
 */

char **parser(char *str)
{
	size_t j = 0, sep = 0;
	char **res = NULL;
	char *word = NULL;

	str = special_char_finder(str, "#");
	sep = count_sep(str, ' ');
	res = malloc(sizeof(char *) * (sep + 2));
	if (!res)
		return (NULL);
	word = strtok(str, " \n");
	while (word)
	{
		res[j] = word;
		word = strtok(NULL, " \n");
		j++;
	}
	res[j] = NULL;
	return (res);
}

/**
 * findpath - entry point
 * @env: enviroment array
 * uses getenv to find path and separates it by :
 * and arranges it into an array of strings
 * Return: the array of strings, where each string is a dir in PATH
 */

char **findpath(char **env)
{
	int j = 0, size = 0;
	char *path;
	char **res;
	char *word;

	path = _getenv("PATH", env);
	size = count_dirs(path);
	res = malloc(sizeof(char *) * (size));
	if (!res)
	{
		return (NULL);
	}
	word = strtok(path, ":=");
	while (word)
	{
		res[j] = word;
		word = strtok(NULL, ":=");
		j++;
	}
	res[j] = NULL;
	return (res);
}

/**
 * _getenv - entry point
 * @name: word to search for in the environment
 * @env: enviroment array
 * Return: line in the environment where name is found
 */

char *_getenv(const char *name, char **env)
{
	int i = 0, j = 0;
	char *word;

	for (i = 0; env[i] != '\0'; i++)
	{
		word = env[i];
		for (j = 0; name[j] != '\0'; j++)
		{
			if (name[j] != word[j])
				break;
		}
		if ((name[j] == '\0') && (word[j] == '='))
			return (word);
	}
	return (NULL);
}
