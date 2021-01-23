#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Inputs should be in the following format: p3 K F\n");
        exit(0);
    }

    int K = atoi(argv[1]);
    char F[1000];
    strcpy(F, argv[2]);
    int noOfRandomAccess = 1000;

    struct timeval tvStart;
    struct timeval tvEnd;
    struct stat stats;
    long randomPos;

    int fd = open(F, O_RDONLY);
    stat(F, &stats);
    long max = stats.st_size;
    char buf[K + 1];

    gettimeofday(&tvStart, NULL);

    for (int i = 0; i < noOfRandomAccess; i++)
    {
        randomPos = rand() % (max + 1 - 0);
        lseek(fd, randomPos, SEEK_SET);
        read(fd, buf, K);
    }

    gettimeofday(&tvEnd, NULL);

    time_t sec = (tvEnd.tv_sec - tvStart.tv_sec) / noOfRandomAccess;
    suseconds_t usec = (tvEnd.tv_usec - tvStart.tv_usec) / noOfRandomAccess;

    printf("%ld seconds and %ld microseconds\n", sec, usec);
    close(fd);

    return 0;
}