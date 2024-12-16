#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void error_handling(char *message) {
    printf("%s (press ENTER to end process)", message);
    getchar();
    exit(EXIT_FAILURE);
}
