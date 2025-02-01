#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Installing BlackHole...\n");
    int install_status = system("sudo installer -pkg ./BlackHole.pkg -target /");

    if (install_status != 0) {
        printf("Installation failed! Run manually if needed.\n");
        return 1;
    }

    printf("BlackHole installed successfully.\n");
    return 0;
}

