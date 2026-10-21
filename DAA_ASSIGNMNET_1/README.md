# DAA Assignment 1: Merge Sort - all IPL batting records

Reads IPLBatters.csv and prints every player-team-season row in descending runs order. The 2,617 records cover 2008-2024. The same player can legitimately occur in several seasons or teams. Merge Sort is stable; comparisons, merge count, total runs and sorting-only time are printed.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "DAA_Assignment_1.cpp" -o Assignment1.exe
.\Assignment1.exe
```

## Input

CSV columns: name,team,runs,season. No keyboard input. input.txt mirrors the full CSV as a reference; the executable reads IPLBatters.csv.

## Output

`Assignmnet_1_Output.txt` is the actual captured output of the current program and saved input. The PDF contains the assignment write-up and pseudocode. Detailed program results are kept in the text output file on GitHub; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

O(N log N) time and O(N) peak auxiliary memory.

## Viva notes and scope

The original warehouse statement uses inventory quantities ascending; this program demonstrates the same algorithm with IPL runs descending. No million-row performance claim is made.

See [DATASET_SOURCE.md](DATASET_SOURCE.md) for the Kaggle source, exact preparation and archive checksum. Every CSV record is displayed; there is no top-ten cutoff.
