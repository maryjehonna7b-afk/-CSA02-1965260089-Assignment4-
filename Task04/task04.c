#include <stdio.h>

struct account {
    int number;
    float balance;
};

/* Repaired: a pointer lets the function update the original array element. */
void addInterest(struct account *a, float rate)
{
    if (a != NULL) {
        a->balance = a->balance + a->balance * rate / 100.0f;
    }
}

/* Original pass-by-value behaviour, retained to demonstrate the defect. */
void addInterestByValue(struct account a, float rate)
{
    a.balance = a.balance + a.balance * rate / 100.0f;
    printf("Address of local copy inside by-value function: %p\n", (void *)&a);
}

int main(void)
{
    struct account list[3] = {
        {101, 5000.0f},
        {102, 12000.0f},
        {103, 800.0f}
    };
    struct account *p = list;
    int i;

    printf("Address of list[0] in main: %p\n", (void *)&list[0]);
    addInterestByValue(list[0], 4.0f);
    printf("Balance after by-value call: %.2f\n", list[0].balance);

    for (i = 0; i < 3; i++) {
        addInterest(&list[i], 4.0f);
    }

    printf("First account using pointer: %d %.2f\n",
           p->number, p->balance);

    for (i = 0; i < 3; i++) {
        printf("%d %.2f\n", list[i].number, list[i].balance);
    }

    return 0;
}
