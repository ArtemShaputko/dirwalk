#include <sys/types.h>
#include <dirent.h>

typedef struct
{
    unsigned int link : 1;
    unsigned int dir  : 1;
    unsigned int file : 1;
    unsigned int sort : 1;
} option;

option parseCmdOptions(int argc, char** argv);
char* parseCmdPath(int argc, char** argv);
void showDir(char * dirName, option opt);
void printFiles(size_t count, char* dirName, struct dirent **array, option opt);
char* mergePath(const char* dir, size_t lenDirName, const char* file);


