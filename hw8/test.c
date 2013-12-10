#include <stdio.h>
#include "vitals.h"

int main() {
    readfile("test.data");
    printf("There were %d values.\n", count());
    printf("The median value is %f.\n", median());
    release_memory();
    return 0;
}
