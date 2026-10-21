# DAA Assignment 6: 0/1 Knapsack - named truck packages

Prints every package with weight, utility, whole-package divisibility and take/leave decision. Prints the full DP table for n<=8 and W<=20, followed by named truck contents and totals. The sample selects Food, BabyFood and Medicine: utility 143, weight 13 of 15 kg.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "ReliefKnapsack.cpp" -o Assignment6.exe
.\Assignment6.exe
```

Use the saved input:

```powershell
Get-Content input.txt | .\Assignment6.exe
```

## Input

First line: numberOfItems integerCapacity. Each item: name positiveIntegerWeight nonnegativeIntegerUtility. One-word names. A package is taken at most once or left; fractions are forbidden.

## Output

`Output.txt` is the actual captured output of the current program and saved input. The PDF includes theory, pseudocode, input details and the full output; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

O(N*(W+1)) time and space, pseudo-polynomial in capacity. Limits: n<=200, W<=10000.

## Viva notes and scope

Implements one truck without explicit mandatory perishability priority. Multiple trucks and real-time allocation are extensions. Utility does not guarantee mandatory selection.

## Saved sample input

```text
5 15
Blankets 5 30
Food 6 48
BabyFood 3 35
Medicine 4 60
Water 7 28
```
