# Task 2 – Courier Parcel Tracking

## 2.1 Entities and fields

- **Date:** day, month, year.
- **Address:** receiver city and PIN code.
- **Parcel:** parcel ID, weight, destination address and booking date.
- **Booking list:** an array of `struct parcel` records for the day's bookings.

`struct address` and `struct date` are nested inside `struct parcel`.

## 2.2 Structure definitions

The definitions are implemented in `task02.c`. The array `list[3]` represents the day's parcel bookings. For the complete scenario, extend the parcel model with a `from` address, a service enum (`NORMAL` / `EXPRESS`) and a `charge` field. For example:

```c
struct parcel_full {
    int id;
    float weight;
    struct address from;
    struct address to;
    struct date booked;
    enum service_type { NORMAL, EXPRESS } service;
    float charge;
};
```

The supplied `task02.c` deliberately retains the assignment's given starter structure so that its required expected output remains unchanged.

## 2.3 SIMATS-style pseudocode

### (a) Sort parcels by weight

```text
ALGORITHM SortParcelsByWeight(P, n)
BEGIN
    FOR i ← 0 TO n - 2
        minIndex ← i
        FOR j ← i + 1 TO n - 1
            IF P[j].weight < P[minIndex].weight THEN
                minIndex ← j
            END IF
        END FOR
        IF minIndex ≠ i THEN
            SWAP P[i] AND P[minIndex]
        END IF
    END FOR
END
```

### (b) List parcels for a receiver city

```text
ALGORITHM ListParcelsForCity(P, n, targetCity)
BEGIN
    FOR i ← 0 TO n - 1
        IF P[i].to.city = targetCity THEN
            DISPLAY P[i].id, P[i].weight, P[i].to.pincode
        END IF
    END FOR
END
```

## 2.4 Access paths

For the third parcel:
- Array and dot operator: `list[2].to.pincode`
- Pointer and arrow operator: `ptr->to.pincode`, where `ptr = &list[2]`

## Complexity and alternative flat design

Selection sort performs **O(n²)** comparisons and uses **O(1)** extra space. A swap uses three whole-structure assignments; the structure's measured size is `sizeof(struct parcel)` bytes per structure object assignment (the C standard does not require a particular machine instruction or literal byte-copy implementation).

A flat parcel structure would place destination city, PIN, and date fields directly in `struct parcel`. Access would be shorter, for example `p->receiver_city` and `p->booking_day`, but the reusable `address` and `date` types would be lost. Nested structures improve reuse and group related fields. Actual sizes should be compared using `sizeof` on the compiler used.

## Expected output

```text
502 1.2 kg Chennai-600077 12/10/2026
503 2.8 kg Coimbatore-641001 13/10/2026
501 4.5 kg Madurai-625001 12/10/2026
Bytes in one whole-structure assignment: (compiler dependent)
Receiver PIN using dot: 625001
Receiver PIN using arrow: 625001
```
