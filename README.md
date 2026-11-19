# CSA02 – Assignment 4
## Modelling Real-World Data with Structures and Unions

**Student name:** Mary Jehonna S.  
**Register number:** 1965260089  
**Course:** CSA02 – C Programming  
**Compiler:** GCC (record the version installed on your computer)

> Please verify the name and register number before submission. Replace them if your college records use a different format.

## Repository structure

```text
CSA02-1965260089-Assignment4/
├── README.md
├── Task01/
│   ├── task01.c
│   └── DESIGN.md
├── Task02/
│   ├── task02.c
│   └── DESIGN.md
├── Task03/
│   ├── task03.c
│   └── DESIGN.md
├── Task04/
│   ├── task04.c
│   └── DESIGN.md
├── Task05/
│   ├── task05_static_auto.c
│   ├── task05_extern_main.c
│   ├── task05_extern_counter.c
│   ├── task05_register.c
│   └── DESIGN.md
└── Task06/
    ├── task06.c
    └── DESIGN.md
```

## Compiler and commands

Use GCC with warnings enabled. Open a terminal in the relevant task folder.

Check your compiler version:

```bash
gcc --version
```

Compile and run each task:

```bash
# Task 1
gcc -std=c11 -Wall -Wextra -pedantic task01.c -o task01
./task01

# Task 2
gcc -std=c11 -Wall -Wextra -pedantic task02.c -o task02
./task02

# Task 3
gcc -std=c11 -Wall -Wextra -pedantic task03.c -o task03
./task03

# Task 4
gcc -std=c11 -Wall -Wextra -pedantic task04.c -o task04
./task04

# Task 5A: static and automatic counters
gcc -std=c11 -Wall -Wextra -pedantic task05_static_auto.c -o task05a
./task05a

# Task 5B: extern counter (compile BOTH source files together)
gcc -std=c11 -Wall -Wextra -pedantic task05_extern_main.c task05_extern_counter.c -o task05b
./task05b

# Task 5C: register loop variable demonstration
gcc -std=c11 -Wall -Wextra -pedantic task05_register.c -o task05c
./task05c

# Task 6
gcc -std=c11 -Wall -Wextra -pedantic task06.c -o task06
./task06
```

On Windows, run the generated `.exe` files (for example, `task01.exe`) instead of `./task01`.

## Task result summary

- **Task 1:** Diagnoses a parallel-array patient design and demonstrates a nested structure design with a pointer-based insertion function.
- **Task 2:** Models courier parcels with nested address/date structures, prints through `->`, and selection-sorts whole structures by weight.
- **Task 3:** Demonstrates the memory advantage of a tagged union and prints only the member selected by its tag.
- **Task 4:** Shows why pass-by-value does not update the original account, then repairs the function using a structure pointer.
- **Task 5:** Compares automatic, static, extern and register storage-class use. The extern example uses two C files.
- **Task 6:** Implements a small canteen inventory and billing program with packaged, cooked and combo item variants, stock checks, expiry warnings and revenue-sorted sales.

## Before submitting

1. Run every program yourself using the exact commands above.
2. Compare your actual output with the sample output shown in each task's `DESIGN.md`.
3. Take screenshots of your own compiler/terminal execution and save them in the matching task folder. Screenshots are intentionally not fabricated or included in this starter package.
4. Update compiler version and any output differences in this README.
5. Create the GitHub repository named `CSA02-1965260089-Assignment4` (or use your correct register number).
6. Commit progressively, at least one commit per task. Example:

```bash
git add Task01
git commit -m "Complete Task 1 patient data design"
```

Repeat for Task02 through Task06, then commit the README.
7. Share the repository with the faculty and paste the working repository URL on the assignment and report cover page.

## Important notes

- The assignment asks for individual work and may include a viva. Understand every structure, pointer expression, storage class and complexity explanation before submission.
- Task 3 `sizeof` values are platform/compiler dependent. The assignment gives expected values for a typical 64-bit GCC environment; record the values printed on your system.
- In Task 4, memory addresses change between executions. Use your own run's addresses as evidence.
- The sample data in Task 6 is illustrative. You can change it and test additional cases.
