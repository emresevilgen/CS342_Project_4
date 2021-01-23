#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Inputs should be in the following format: p2 P\n");
        exit(0);
    }

    char path[1000];
    strcpy(path, argv[1]);

    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        printf("Unable to read directory");
        exit(0);
    }

    struct dirent *entry;
    struct stat stats;

    while (entry = readdir(dir))
    {
        if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
            continue;

        printf("---------\n");
        printf("Name: %s \n", entry->d_name);

        char entryPath[1000];
        strcpy(entryPath, path);
        strcat(entryPath, entry->d_name);
        
        if (stat(entryPath, &stats) == 0)
        {
            printf("Inode number: %ld \n", stats.st_ino);
            printf("Type: %d \n", entry->d_type);
            printf("Number of blocks: %ld \n", stats.st_blocks);
            printf("Size in bytes: %ld \n", stats.st_size);
            printf("Userid: %d \n", stats.st_uid);
        }
        else
        {
            printf("Type: %d - ", entry->d_type);
        }
    }

    closedir(dir);
    return 0;
}