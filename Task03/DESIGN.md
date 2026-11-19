# Task 3 – Unions and Memory Layout

## 3.1 Structure versus tagged union

A structure containing `float celsius`, `int percent` and `char status[8]` stores space for all three members simultaneously. It is straightforward but wastes space when each packet contains only one kind of value. One possible definition is:

```c
struct reading_all {
    enum kind type;
    float celsius;
    int percent;
    char status[8];
};
```

The implemented `struct reading` contains an enum tag and a union. The union members share the same storage. The tag identifies which member is currently valid. This is suitable when exactly one value is active in each packet.

## 3.2 Size and alignment

On the common 64-bit GCC ABI used by the assignment:
- `sizeof(union)` is expected to be 8 because the largest member is `char status[8]`.
- The enum tag is commonly 4 bytes.
- The union commonly requires 4-byte alignment.
- The structure therefore commonly occupies 12 bytes: 4-byte tag + 8-byte union.

The structure is not 4 + 4 + 4 + 8 because the union does not allocate separate storage for all three members. The members overlap. These values are ABI/compiler dependent; use the program's `sizeof` output as the measured result.

## 3.3 Tagged-union printing

`show()` uses `switch (r->type)` and reads only the member corresponding to the tag.

## 3.4 Misuse experiment

The program stores a temperature and then deliberately reads `percent`. This is not a valid way to interpret the value. In C, reading a different union member can produce a representation-dependent result; do not expect a meaningful humidity value. The tag must always be checked before reading the union.

## Alternative representations and complexity

- **Three separate arrays:** Store temperatures, humidity values and status strings in separate arrays. This can avoid a tag for each entry, but requires an external way to map packet order/type and can make a mixed chronological log harder to traverse. Reading a known item can be O(1); locating the correct typed array/index may need extra bookkeeping.
- **Dynamically allocated objects through `void *`:** Each object needs allocation and a type tag elsewhere. Access requires casts and careful memory management. Allocation metadata and pointer storage add overhead; allocation/free may be more expensive than using a compact fixed-size array.
- **Tagged union:** One array traversal and a switch per packet; O(1) access to a known packet and O(n) storage for n packets. The union size is the size of its largest member plus any required alignment, with the tag stored alongside it.

## Expected output

The first four lines should match the assignment on a typical target:

```text
sizeof union = 8, sizeof struct reading = 12
Temp 31.5 C
Humidity 68 %
Status OK
```

The additional misuse line is intentionally implementation-dependent.
