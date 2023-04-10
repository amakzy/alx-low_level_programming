#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/**
 * error - prints an error message and exits with a specified exit code
 * @msg: the error message to print
 * @file: the file associated with the error
 * @exit_code: the exit code to use when exiting the program
 */
void error(char *msg, char *file, int exit_code)
{
	dprintf(STDERR_FILENO, "%s %s\n", msg, file);
	exit(exit_code);
}

/**
 * main - copies the contents of one file to another file
 * @argc: the number of command-line arguments
 * @argv: an array of command-line arguments
 *
 * Return: 0 if successful, non-zero otherwise
 */
int main(int argc, char *argv[])
{
	int file_from, file_to;
	ssize_t nchars;
	char buffer[BUFFER_SIZE];

	if (argc != 3)
		error("Usage: cp file_from file_to", "", 97);

	file_from = open(argv[1], O_RDONLY);
	if (file_from == -1)
		error("Error: Can't read from file", argv[1], 98);

	file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (file_to == -1)
		error("Error: Can't write to", argv[2], 99);

	while ((nchars = read(file_from, buffer, BUFFER_SIZE)) > 0)
	{
		if (write(file_to, buffer, nchars) != nchars)
			error("Error: Can't write to", argv[2], 99);
	}

	if (nchars == -1)
		error("Error: Can't read from file", argv[1], 98);

	if (close(file_from) == -1)
		error("Error: Can't close fd", argv[1], 100);

	if (close(file_to) == -1)
		error("Error: Can't close fd", argv[2], 100);

	return (0);
}
