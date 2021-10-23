#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    for (int i = 1; i < 100; i++) {
        errno = i;
	printf ("errno = %d %s\n", errno, strerror(errno));
    }
}
