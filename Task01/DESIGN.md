# Task 1 – Data Design Review

## 1.1 Deficiencies in the original design

1. **Parallel arrays:** A patient's name, age, phone, blood pressure and date are stored at the same index in separate arrays. If one array is shifted or updated incorrectly, details from different patients can become mixed.
2. **Phone number size:** `char phone[100][10]` stores at most nine visible characters plus the terminating `'\0'`. A ten-digit phone number needs at least 11 characters. Phone numbers should be strings because arithmetic is not performed on them.
3. **Blood pressure in one float:** A reading such as 120/80 contains two separate integer measurements. A single floating-point value cannot represent the two fields clearly or validate them independently.
4. **Date stored as text:** A text date is harder to validate, compare and sort. A date structure stores day, month and year separately.
5. **No capacity check:** `count` can exceed 99 and write outside the arrays, causing undefined behaviour and possible memory corruption.
6. **Global state:** A global `count` and global arrays make the function dependent on hidden shared state and make reuse/testing harder.
7. **Sorting difficulty:** Sorting patients requires swapping the corresponding entries in every array. Forgetting one array corrupts the association between fields.

## 1.2 Repaired structure design

The program in `task01.c` uses:
- `Date` for day, month and year.
- `BloodPressure` for systolic and diastolic readings.
- `Patient` to group all details belonging to one patient.
- `addPatient(const Patient *)` to accept a pointer and copy a complete record after checking capacity.

A safer scalable extension would pass a register object containing both the array and count rather than using globals. The compact example retains a simple fixed-size register for demonstration.

## 1.3 Design defence (under 100 words)

An array of structures keeps each patient's related fields together, so a complete record can be copied or swapped as one unit. Sorting by age is simpler because only whole `Patient` objects need to be exchanged. Functions can receive a pointer to one patient instead of receiving many separate arrays and indices. Nested `Date` and `BloodPressure` structures make the meaning of each field clear and allow those data types to be reused. New fields can be added to `Patient` without maintaining several parallel arrays.

## Alternative concept and complexity

Parallel arrays can be useful when a program processes only one field at a time, when data is column-oriented, or when memory/cache efficiency for a particular field is important.

For a simple comparison sort such as selection sort:
- Both designs take **O(n²)** comparisons.
- With an array of structures, a swap moves one complete `Patient` record.
- With parallel arrays, a swap must exchange the matching element in every array (five field arrays in the original design).
- Both designs use **O(n)** storage for the records.
- Actual byte usage differs because of field sizes, array capacities and structure padding. Use `sizeof(Patient)` on the target compiler to measure the structure representation. Parallel arrays have no per-record structure padding between unrelated arrays, though each array's element representation still has its own size.

## Sample output

```text
Patient register (2 records)
Ananya               Age:21 Phone:9876543210 BP:120/80 Visit:19/11/2026
Karthik              Age:35 Phone:9123456780 BP:130/85 Visit:18/11/2026
```
