#include "shell.h"
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
/*Initialize an array'info_t'structures with'INFO_INIT' values*/
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"

			"add $3, %0"

			: "=r" (fd)

			: "r" (fd));

/*Inline assembly code that moves the value of 'fd' into the '%0' register and adds 3 to it. 
    // The modified value of 'fd' is stored back into 'fd'.*/
	if (ac == 2)
	{
		/*Attempt to open the file specified by the second command-line argument in read-only mode*/
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{

			if (errno == EACCES)
				exit(126);/*Exit with status 126 if there is a permission denied error*/

			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				/*Exit with status 127*/
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

/*Populate the environment list using the 'info' array*/
	populate_env_list(info);
	/*Read the command history using the 'info' array*/
	shellhistory_read(info);
/*Display the command prompt and handle user input using the 'info' array and command-line arguments*/
	prompt(info, av);

	return (EXIT_SUCCESS);
}