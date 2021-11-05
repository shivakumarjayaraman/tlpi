/* t_writev.c

   Demonstrate the use of the writev() system call to perform "scatter I/O".

   (This program is merely intended to provide a code snippet for the book;
   unless you construct a suitably formatted input file, it can't be
   usefully executed.)

   This is used to create a file that can be read by Mike Kerrisk's t_readv program
*/

#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd;
    struct iovec iov[3];
    struct stat myStruct;       /* First buffer */
    int x = 23;                 /* Second buffer */
#define STR_SIZE 100
    char str[STR_SIZE];         /* Third buffer */

    for (int i = 0; i < STR_SIZE; i++) {
        str[i] = 'a' + (i%26);
    }
    str[STR_SIZE-1] = 0;  // null terminate, so it can be printf'ed 

    ssize_t numWritten, totRequired;


    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    // Not checking return value, which is bad .. 
    stat("./t_writev.c", &myStruct);


    totRequired = 0;

    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    totRequired += iov[2].iov_len;

    numWritten = writev(fd, iov, 3);
    if (numWritten == -1)
        errExit("writev");

    if (numWritten < totRequired)
        printf("Written fewer bytes than requested\n");

    /*FIXME: should use %zd here, and remove (long) cast */
    printf("total bytes written : %ld; bytes read: %ld\n",
            (long) totRequired, (long) numWritten);
    exit(EXIT_SUCCESS);
}
