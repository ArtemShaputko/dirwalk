#define _DEFAULT_SOURCE

#include "func.h"
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define NAMESIZE 255

option parseCmdOptions(int argc, char** argv)
{
    option ret = {0};
    int c;
    while((c = getopt(argc, argv, "lfds")) != -1)
    {
        switch (c)
        {
        case 'l':
            ret.link = 1;
            break;
        case 'f':
            ret.file = 1;
            break;
        case 'd':
            ret.dir = 1;
            break;
        case 's':
            ret.sort = 1;
            break;
        default:
            break;
        }
    }
    if(!ret.link && !ret.dir && !ret.file) return (option){1,1,1,ret.sort};
    else return ret;
}

char *parseCmdPath(int argc, char **argv)
{
    DIR* directory;
    char* dirName = malloc(NAMESIZE*sizeof(char));

    if(argc>1 && argv[argc-1][0] != '-')
    {
        directory = opendir(argv[argc-1]);
        strcpy(dirName, argv[argc-1]);
    }
    else
    {
        directory = opendir(".");
        strcpy(dirName,".");
    } 
    if(!directory)
    {
        printf("Wrong path\n");
        free(directory);
        exit(errno);
    }
    free(directory);
    return dirName;
}

void showDir(char *dirName, option param)
{
    struct dirent **files;
    long long int count;
    if(param.sort) count = scandir(dirName, &files, NULL, alphasort);
    else count = scandir(dirName, &files, NULL, NULL);

    if(count < 0)
    {
        printf("Can`t open dir %s\n", dirName);
    }
    else
        printFiles(count, dirName, files, param);
}

void printFiles(size_t count, char*dirName, struct dirent **array, option param)
{
    char* fullPath;
    for(int i = 0; i<count; i++)
    {
        fullPath = mergePath(dirName, strlen(dirName), array[i]->d_name);
        if(array[i]->d_type==DT_DIR)
        {
            if(strcmp(array[i]->d_name, ".") != 0
                    && strcmp(array[i]->d_name, "..") != 0)
            {
                if(param.dir) printf(" dir | %-s\n", fullPath);
                showDir(fullPath, param);
            }
        }
        if(param.file && array[i]->d_type==DT_REG)
            printf("file | %-s\n", fullPath);
        if(param.link && array[i]->d_type==DT_LNK)
            printf("link | %-s\n", fullPath);
        free(array[i]);
        free(fullPath);
    }
    free(array);
}

char* mergePath(const char* dir, size_t lenDirName, const char* file)

{
    char * fullPath = calloc(PATH_MAX, sizeof(char));
    sprintf(fullPath, "%s/%s", strcmp(dir, "/") == 0? "" : dir, file);
    return fullPath;
}
