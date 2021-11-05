#include "tlpi_hdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        usageErr("%s <file>\n", argv[0]);
        errExit("Usage error");
    }

    int fd = open(argv[1], O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        errExit("Error opening file %s\n", argv[1]);
    }

    off_t off = lseek(fd, 0, SEEK_SET);
    printf ("New offset is %ld\n", off);
    int numW = write(fd, "Foo", 3);
    if (numW != 3) {
        errExit("Error writing file");
    }
    close(fd);
}
