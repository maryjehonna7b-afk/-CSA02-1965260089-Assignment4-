# Task 5 – Storage Classes

## 5.1 Four implementations

- **auto:** `auto_token()` initializes a local variable to 1000 on every call. Each call returns 1001.
- **static:** `next_token()` has a static local variable. It is initialized once and retains its value between calls.
- **extern:** `shared_token_counter` is defined once in `task05_extern_counter.c` and declared with `extern` in `task05_extern_main.c`. Both files are linked into one executable.
- **register:** `task05_register.c` uses a register loop variable. The compiler may keep it in a CPU register; this is only a request/hint and modern compilers choose register allocation themselves.

## Expected outputs

`task05_static.c`:
```text
static: 1001 1002 1003
```

`task05_auto.c`:
```text
auto : 1001 1001 1001
```

`task05_extern_main.c` + `task05_extern_counter.c`:
```text
extern: 1003 1002 1001
```
The extern example's single `printf` has multiple function calls as arguments. C does not specify the order in which those arguments are evaluated, so the displayed order can differ. For a predictable sequence, call the function in separate statements.

`task05_register.c`:
```text
Sum from 1 to 5 = 15
```

## 5.2 Two independent counters

A static-local implementation can use two separate static variables (for example, `veg_token` and `nonveg_token`) or a static array indexed by category. An extern implementation can expose two global counters. An automatic variable cannot retain a sequence between separate calls unless the caller owns and passes the counter. The register class is intended for local variables such as loop indices, not persistent counters.

The cleanest scalable design is often caller-owned state passed by pointer:
`int next_token(int *counter) { ++(*counter); return *counter; }`
The caller can maintain separate `veg` and `nonveg` counters without hidden shared state.

## 5.3 Comparison

| Storage class | Scope | Lifetime | Default initialization | Main consideration |
|---|---|---|---|---|
| auto | Block | Until block exits | Indeterminate for uninitialized local | Fresh value on each call |
| static local | Block | Entire program | Zero if not explicitly initialized | Retains value between calls |
| extern global | File/program linkage as declared | Entire program | Zero if defined without initializer | Shared state; can be modified from multiple files |
| register | Block | Until block exits | Indeterminate if uninitialized | Address cannot be taken with `&` |

Taking the address of a `register` object is prohibited by the C language because the declaration requests register storage and the object is not addressable through the `&` operator.

## Alternative: caller-owned counter

```c
int next_token(int *counter)
{
    if (counter == NULL) {
        return -1;
    }
    ++(*counter);
    return *counter;
}
```

Initialize `int veg = 1000; int nonveg = 2000;`, then call `next_token(&veg)` and `next_token(&nonveg)`. Each call takes O(1) time. The counters live as long as the caller's variables and require O(1) space each. This makes independent counters straightforward and avoids hidden global/static state.
