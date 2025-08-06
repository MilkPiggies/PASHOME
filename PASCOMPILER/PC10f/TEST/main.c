#include <stdio.h>
#include <stdlib.h>

char* decimal_to_hex(int decimal) {
    char* hex_value = malloc(5 * sizeof(char)); // 4 digits + null terminator
    sprintf(hex_value, "%04x", decimal);
    return hex_value;
}

int main() {
    int decimal = 1200;
    char* hex_value = decimal_to_hex(decimal);
    printf("%s\n", hex_value);
    free(hex_value);
    return 0;
}
