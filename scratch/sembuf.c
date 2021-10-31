#include "tlpi_hdr.h"

#include <sys/ipc.h>
#include <sys/sem.h>


int main() {
    struct sembuf s = { .sem_num = 3, .sem_op = -1, .sem_flg = SEM_UNDO };
    printf ("%d\n", s.sem_num);
}
