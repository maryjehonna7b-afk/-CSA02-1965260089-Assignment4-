#include <stdio.h>

int auto_token(void)
{
    int token = 1000;
    return ++token;
}

int main(void)
{
    int a1 = auto_token();
    int a2 = auto_token();
    int a3 = auto_token();

    printf("auto : %d %d %d\n", a1, a2, a3);
    return 0;
}
