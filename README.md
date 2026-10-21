# Design and Analysis of Algorithms Assignments

**Soham Kulkarni | PRN 124B1F056 | PCCoE Pune | Batch A3**

Eight C++ programs with matching inputs, detailed captured text outputs and PDF reports. C++ code is separate from the PDFs. The PDFs contain the assignment write-ups and pseudocode. Complete program results are kept separately in the GitHub text output files.

| No. | Assignment | Result |
| --- | --- | --- |
| 1 | [Merge Sort](DAA_ASSIGNMNET_1) | All 2,617 IPL player-team-season records sorted by runs |
| 2 | [Quick Sort](DAA_ASSIGNMNET_2) | All 4,803 TMDB movies sorted by rating in the saved run |
| 3 | [Fractional Knapsack](DAA_ASSIGNMENT_3) | Named boat supplies, divisibility and loading tables |
| 4 | [Dijkstra](DAA_ASSIGNMENT_4) | Trace, distances, route legs and road update |
| 5 | [Multistage routing](DAA_ASSIGNMENT_5) | DP table, fastest/cheapest routes and closures |
| 6 | [0/1 Knapsack](DAA_ASSIGNMENT_6) | Named whole packages, DP table and truck contents |
| 7 | [Graph Coloring](DAA_ASSIGNMENT_7) | Named exam colors, groups and conflict checks |
| 8 | [LC Branch and Bound TSP](DAA_ASSIGNMENT_8) | Bounds, search trace, tour legs and deadline check |

Open an assignment folder and follow its README for the exact compile command and input format. For keyboard-input programs in PowerShell, use `Get-Content input.txt | .\AssignmentN.exe`. Assignment 1 reads its CSV directly; Assignment 2 needs both movies.csv and its keyboard choice.

## Dataset sources

- IPL: [Kaggle IPL Complete Dataset (2008-2024)](https://www.kaggle.com/datasets/patrickb1912/ipl-complete-dataset-20082020). Aggregate regular-innings batsman_runs by batter, team and calendar year; retain all 2,617 resulting groups. No fabricated rows or repeated sample padding.
- Movies: [Kaggle TMDB 5000 Movie Dataset](https://www.kaggle.com/datasets/tmdb/tmdb-movie-metadata). Retain all 4,803 rows, with title, vote_average, release year and decimal popularity. Missing release year is 0.

Each dataset folder has preparation notes and the downloaded archive SHA-256. Sorting timing excludes file reading and printing.

## Validation

All eight compile with C++11, `-Wall -Wextra` without warnings. Ninety-six execution checks cover full-record ordering and preservation, CSV quoting, independent fractional/0-1 knapsack calculations, Floyd-Warshall shortest-path comparisons, enumerated multistage routes, coloring conflicts and exhaustive small TSP comparisons. Greedy coloring does not generally prove minimum colors; TSP retains factorial worst-case complexity. Reports distinguish implemented behavior from optional extensions.
