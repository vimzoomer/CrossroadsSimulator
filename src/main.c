#include "simulation.h"
#include "stdio.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./program <arg1> <arg2>\n");
        return 1;
    }

    simulate(argv[1], argv[2]);
    return 0;
}


