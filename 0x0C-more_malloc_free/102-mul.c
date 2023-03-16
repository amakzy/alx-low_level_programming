#include <stdio.h>
#include <stdlib.h>

/**
 * _isdigit - checks if a string is composed of only digits
 * @s: string to check
 *
 * Return: 1 if the string is composed only of digits, 0 otherwise
 */
int _isdigit(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/**
 * main - multiplies two positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	int i, j, len1, len2, *result;

	if (argc != 3 || !_isdigit(argv[1]) || !_isdigit(argv[2]))
	{
		printf("Error\n");
		return (1);
	}

	len1 = 0;
	while (argv[1][len1])
		len1++;

	len2 = 0;
	while (argv[2][len2])
		len2++;

	result = calloc(len1 + len2, sizeof(*result));
	if (!result)
	{
		printf("Error\n");
		return (1);
	}

	for (i = len1 - 1; i >= 0; i--)
	{
		for (j = len2 - 1; j >= 0; j--)
		{
			result[i + j + 1] += (argv[1][i] - '0') * (argv[2][j] - '0');
			result[i + j] += result[i + j + 1] / 10;
			result[i + j + 1] %= 10;
		}
	}

	i = 0;
	while (result[i] == 0 && i < len1 + len2 - 1)
		i++;

	for (; i < len1 + len2; i++)
		printf("%d", result[i]);
	printf("\n");

	free(result);
	return (0);
}