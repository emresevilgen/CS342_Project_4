#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("Inputs should be in the following format: p1 N\n");
		exit(0);
	}

	int N = atoi(argv[1]);

	int fd = open("./file", O_RDWR | O_CREAT, 0777);
	char zero = 0;
	int iterNo = 4094 * N;
	for (int i = 0; i < iterNo; ++i)
		write(fd, &zero, 1);
	close(fd);

	return 0;
}