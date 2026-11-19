#include <stdio.h>

int next_token(void)
{
    static int token = 1000;
    token++;
    return token;
}

int main(void)
{
    int s1 = next_token();
    int s2 = next_token();
    int s3 = next_token();

    printf("static: %d %d %d\n", s1, s2, s3);
    return 0;
}
