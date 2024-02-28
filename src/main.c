#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include "func.h"

int main(int argc, char** argv)
{
    option param = parseCmdOptions(argc, argv);
    char * dirName = parseCmdPath(argc, argv);
    showDir(dirName, param);
    free(dirName);
    return 0;
}