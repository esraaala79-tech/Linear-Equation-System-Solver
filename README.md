# Linear Equation System Solver (C++)

A C++ console program to **read, manipulate, and solve systems of linear equations** using **Cramer's Rule**.  
This project demonstrates core **linear algebra concepts** and **matrix operations** in a simple command-line interface.


## Features

- Parse linear equations in standard algebraic format, e.g., `2x1 + 3x2 = 5`
- Display equations and specific variable columns
- Perform algebraic operations:
  - Add equations
  - Subtract equations
  - Substitute variables
- Calculate the determinant of the coefficient matrix
- Solve the system of equations using **Cramer's Rule**
- Interactive command-driven interface

---

## Input Format

1. First line: number of equations `n`
2. Next `n` lines: equations in string format
3. Commands to manipulate and solve the system, e.g.:

```text
num_vars
equation 1
add 1 2
substitute x1 1 2
D_value
solve
quit
