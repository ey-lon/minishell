#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int	fd[2];
	char str[3];
	int r;

	read(0, str, 3);
	r = atoi(str) + 2;
	printf("%i\n", r);
	return (0);
}