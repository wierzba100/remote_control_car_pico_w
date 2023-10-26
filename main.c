#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/stdio.h"


int main() {
    stdio_init_all();
    printf("Hello World\n");

    return 0;
}