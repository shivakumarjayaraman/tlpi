#include "tlpi_hdr.h"

int main() {
    const char *arg = "987";
    printf ("%d\n", getInt(arg, 0, "foo"));
    printf ("%d\n", getInt(&arg[1], 0, "foo"));
}
