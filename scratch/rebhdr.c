#include <unistd.h>
#include <linux/reboot.h>

#include "tlpi_hdr.h"

int main()  {
    printf ("%X\n", LINUX_REBOOT_MAGIC1);
    printf ("%X\n", LINUX_REBOOT_MAGIC2);
    printf ("%X\n", LINUX_REBOOT_MAGIC2A);
    printf ("%X\n", LINUX_REBOOT_MAGIC2B);
    printf ("%X\n", LINUX_REBOOT_MAGIC2C);
}

