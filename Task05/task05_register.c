#include <stdio.h>

int main(void)
{
    int total = 0;
    register int i;

    for (i = 1; i <= 5; i++) {
        total += i;
    }

    printf("Sum from 1 to 5 = %d\n", total);
    /* Taking &i is not allowed because i is declared register. */
    return 0;
}
