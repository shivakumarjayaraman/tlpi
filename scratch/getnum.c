#include "tlpi_hdr.h"

int main() {
    const char *arg = "98";
    printf ("%d\n", getInt(arg, 0, "foo"));
}
