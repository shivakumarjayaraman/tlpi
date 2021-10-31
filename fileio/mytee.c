/* mytee.c

   A simple tee implementation

   Usage: mytee [-a] <filenames>

   This program reads from stdin and writes to the command line arguments ..
   It creates a new file, but if -a is specified , appends to the files

   Example:

        mytee -a foo bar
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define MAXLEN 1024
int
main(int argc, char *argv[])
{
    unsigned char buf[MAXLEN];
    ssize_t numRead;

    int flags = O_RDWR;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;                     
    int i = 1;
    if (argc > 1) {
        if (strcmp(argv[i], "-a") == 0) {
            flags |= O_APPEND ;
            i++;
        } else {
            flags |= O_CREAT;
        }
    }
    int numDesc = argc - i + 1;
    int fds[numDesc];
    fds[0] = 1;
    for (int findex=1; i < argc; i++, findex++) {
        fds[findex] = open(argv[i], flags, mode);
        if (fds[findex] < 0) {
             printf("Error opening file %s : %s \n", argv[i], strerror(errno));
             exit(-1);
        }
    }
    while ((numRead = read(0, buf, 1024)) != 0) {
        for (int i = 0; i < numDesc; i++) {
            write(fds[i], buf, numRead);
        }
    }

    for (int i = 0; i < numDesc; i++) {
        close(fds[i]);
    }

    exit(0);
}
