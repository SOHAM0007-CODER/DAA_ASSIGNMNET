# Design and Analysis of Algorithms Assignments

Eight DAA assignments by **Soham Kulkarni**, PRN **124B1F056**,
Pimpri Chinchwad College of Engineering, Pune.

| No. | Assignment | Folder |
| --- | --- | --- |
| 1 | Merge Sort - IPL batters | [Assignment 1](DAA_ASSIGNMNET_1) |
| 2 | Quick Sort - movie records | [Assignment 2](DAA_ASSIGNMNET_2) |
| 3 | Fractional Knapsack | [Assignment 3](DAA_ASSIGNMENT_3) |
| 4 | Dijkstra shortest paths | [Assignment 4](DAA_ASSIGNMENT_4) |
| 5 | SwiftCargo multistage delivery routes | [Assignment 5](DAA_ASSIGNMENT_5) |
| 6 | Disaster relief 0/1 Knapsack - simple version | [Assignment 6](DAA_ASSIGNMENT_6) |
| 7 | Exam timetable Greedy coloring - simple version | [Assignment 7](DAA_ASSIGNMENT_7) |
| 8 | SwiftShip TSP using LC Branch and Bound | [Assignment 8](DAA_ASSIGNMENT_8) |

Each folder includes C++ source, an assignment PDF, `input.txt`, saved output,
and a README. Assignment 4 records its output as a screenshot. Assignment 5
uses an Output.txt transcript. Assignments 6 and 7 contain the simplified
programs; their reports discuss the broader assignment extensions.

## Compile and Run
Open a terminal in the assignment folder. Replace the filename below with
that assignment's C++ filename (see its README):

```powershell
g++ -std=c++11 Program.cpp -o Program.exe
.\Program.exe
```

For programs with keyboard input, PowerShell can supply the saved values:

```powershell
Get-Content input.txt | .\Program.exe
```

On Linux/WSL, compile with `-o Program` and run `./Program`.

## Dataset Notes
- Assignment 1 reads `IPL2025Batters.csv` automatically, with no keyboard
  prompts. Its input.txt mirrors the CSV records. This sample reconstructs
  the ten players visible in the saved output, not the original full dataset.
- Assignment 2 reads `movies.csv`, then takes the sort choice from input.txt.
  Its CSV reconstructs the fifty movie records visible in the saved output.
  The saved output comes from an older code version and shows an ascending
  table; the current source prints the top ten in descending order. Code and
  historical output are retained, with this difference documented.
- For Assignments 3-8, input.txt contains the console values in input order.
- Runtime measurements vary by computer and run.

Compiled executables and object files are excluded from version control.
