# DAA Assignment 3: Fractional Knapsack - named boat supplies

Prints the supply/divisibility table, decreasing utility-per-kg order, loading percentages, fractions, utility contributions and final named boat contents. Sample utility is 265 with 60 kg loaded.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "knapsack.cpp" -o Assignment3.exe
.\Assignment3.exe
```

Use the saved input:

```powershell
Get-Content input.txt | .\Assignment3.exe
```

## Input

First line: itemCount boatCapacity. Then one row per supply: name weight utility. Use one-word names. All input rows represent divisible bulk lots.

## Output

`output.txt` is the actual captured output of the current program and saved input. The PDF includes theory, pseudocode, input details and the full output; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

O(N log N) time; O(N) item storage.

## Viva notes and scope

A fraction is a portion of a bulk lot, not cutting a blanket or sealed medicine. Mixed indivisible-item constraints are not implemented. For whole packages use Assignment 6.

## Saved sample input

```text
5 60
Blankets 20 60
Food 20 100
BabyFood 5 30
Medicine 30 120
Water 15 40
```
