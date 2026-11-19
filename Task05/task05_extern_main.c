#include <stdio.h>

extern int shared_token_counter;

int next_shared_token(void)
{
    shared_token_counter++;
    return shared_token_counter;
}

int main(void)
{
    printf("extern: %d %d %d\n",
           next_shared_token(),
           next_shared_token(),
           next_shared_token());
    return 0;
}
