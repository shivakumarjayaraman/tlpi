#include "tlpi_hdr.h"
#include <fcntl.h>

/*
 * Opens the file specified as cmd line arg, 
 * redirects stdout and stderr to it and writes some
 * stuff into these descriptors.
 * 
 * redirect foo is the equivalent of redirect > foo 2>&1 
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        errExit("Usage : redirect <filename>");
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR, S_IWUSR);
    if (fd < 0) {
        errExit("Error opening file");
    }

    dup2(fd, 1);
    dup2(fd, 2);

    write(1, "Hello STDOUT", 12);
    write(2, "Hello STDERR", 12);

    close(fd);
    //unlink(argv[1]);
}
