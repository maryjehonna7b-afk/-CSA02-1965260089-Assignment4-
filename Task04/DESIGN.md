# Task 4 – Structure Forensics

## 4.1 Defects

1. `addInterest(struct account a, ...)` receives a copy. Updating `a.balance` changes only the local copy; the original element in `list` remains unchanged.
2. `p` is a pointer. `p.number` and `p.balance` are invalid member access expressions. Use `p->number` and `p->balance`, or `(*p).number` and `(*p).balance`.
3. The original code also needs `#include <stdio.h>` for `printf`.

## 4.2 Address evidence

`addInterestByValue()` prints the address of its local parameter copy. `main()` prints the address of `list[0]`. These addresses should be different because the function parameter is a separate object. Exact addresses vary between runs and systems; record your own output.

## 4.3 Repair

The repaired function accepts `struct account *a` and uses `a->balance`. The caller passes `&list[i]`, so the original array element is updated.

Expected balances after 4% interest:
- Account 101: 5200.00
- Account 102: 12480.00
- Account 103: 832.00

## 4.4 Passing guidelines

- **By value:** Use for small structures when the function needs an independent copy and should not modify the caller's object.
- **By pointer:** Use when the function must modify the original object or avoid copying a large structure. Check for a null pointer where appropriate.
- **By const pointer:** Use to read a structure without copying it and prevent accidental modification through that pointer.

## Alternative and complexity

Returning a modified structure by value is another valid approach:

```c
struct account addInterestValue(struct account a, float rate)
{
    a.balance += a.balance * rate / 100.0f;
    return a;
}
/* In main: list[i] = addInterestValue(list[i], 4.0f); */
```

Both pointer and value-return approaches take O(1) time per account and O(n) for n accounts. The value approach copies a structure of `sizeof(struct account)` bytes into the function and returns a result; the pointer approach passes an address and updates the original object. Actual copying/optimization is compiler dependent. A pointer parameter itself requires only pointer-sized argument storage, while the value version needs a parameter/result object conceptually; compilers may optimize copies.

## Sample output (addresses will differ)

```text
Address of list[0] in main: (address)
Address of local copy inside by-value function: (different address)
Balance after by-value call: 5000.00
First account using pointer: 101 5200.00
101 5200.00
102 12480.00
103 832.00
```
