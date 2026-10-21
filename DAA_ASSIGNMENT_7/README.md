# DAA Assignment 7: Graph Coloring - named exam colors

Prints course conflicts, assigned color names, courses grouped by color and PASS/FAIL for each conflict pair. Sample: Red = DAA, CN, Maths; Blue = DBMS, AI; Green = OS.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "ExamScheduler.cpp" -o Assignment7.exe
.\Assignment7.exe
```

Use the saved input:

```powershell
Get-Content input.txt | .\Assignment7.exe
```

## Input

Read course count; one-word course names in ID order; conflict-pair count; each conflicting pair of course IDs (1-based). Every shared-student conflict must be supplied.

## Output

`Output.txt` is the actual captured output of the current program and saved input. The PDF contains the assignment write-up and pseudocode. Detailed program results are kept in the text output file on GitHub; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

O(V^2+E), including slot-flag clearing and grouped output; O(V+E) storage.

## Viva notes and scope

A color denotes one time slot. First colors: Red, Blue, Green, Yellow, Orange, Purple, etc.; slots above 12 use unique Color_13, Color_14, etc. Labels never repeat. Greedy does not generally minimize colors; rooms, student-enrollment parsing and DSATUR/Welsh-Powell implementations are not included.

## Saved sample input

```text
6
DAA DBMS OS CN AI Maths
7
1 2
1 3
2 3
3 4
4 5
2 6
5 6
```
