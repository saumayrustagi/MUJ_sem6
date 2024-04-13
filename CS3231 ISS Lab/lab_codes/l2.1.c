#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MX 5

void playfair(char ch1, char ch2, char key[MX][MX]) {
    int i, j, w, x, y, z;
    for (i = 0; i < MX; i++) {
        for (j = 0; j < MX; j++) {
            if (ch1 == key[i][j]) { w = i; x = j; }
            else if (ch2 == key[i][j]) { y = i; z = j; }
        }
    }
    if (w == y) { x = (x + 1) % 5; z = (z + 1) % 5; }
    else if (x == z) { w = (w + 1) % 5; y = (y + 1) % 5; }
    printf("%c%c", key[w][x], key[y][z]);
}

int main() {
    char key[MX][MX] = { {'P', 'L', 'A', 'Y', 'F'},
                         {'A', 'I', 'R', 'B', 'C'},
                         {'D', 'E', 'G', 'H', 'J'},
                         {'K', 'M', 'N', 'O', 'Q'},
                         {'S', 'T', 'U', 'V', 'W'} };
    char str[] = "HELLO";
    for (int i = 0; i < strlen(str); i++) {
        if (str[i + 1] == '\0') playfair(str[i], 'X', key);
        else if (str[i] == str[i + 1]) playfair(str[i], 'X', key);
        else { playfair(str[i], str[i + 1], key); i++; }
    }
    return 0;
}
