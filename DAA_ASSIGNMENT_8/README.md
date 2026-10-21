# DAA Assignment 8: LC Branch and Bound - detailed delivery tour

Prints directed roads, root lower bounds, feasible seed cost, first 20 expanded search nodes, optimal route, every leg's distance/fuel/cost/time, cumulative cost, deadline check and search statistics.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "SwiftShipTSP.cpp" -o Assignment8.exe
.\Assignment8.exe
```

Use the saved input:

```powershell
Get-Content input.txt | .\Assignment8.exe
```

## Input

Read cities; whole INR/litre fuel price; road count; each road as from to distanceKm fuelMlPerKm travelMinutes; then startCity totalTimeLimit. IDs start at 1; 2-25 cities.

## Output

`Output.txt` is the actual captured output of the current program and saved input. The PDF contains the assignment write-up and pseudocode. Detailed program results are kept in the text output file on GitHub; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

For G generated prefixes and peak queue Q: O(G*(N^2+log(Q+1))) time, O(N^2+Q*N) space. Worst-case search is factorial.

## Viva notes and scope

Fuel cost is minimized subject to a time limit; distance and time are reported, not simultaneously minimized. Sample optimum is route 1->3->2->4->1: 550 INR, 55 km, 5.5 L, 75 min under a 90-minute limit. A 130-minute limit allows 400 INR; 70 minutes is infeasible.

## Saved sample input

```text
4
100
12
1 2 10 100 30
1 3 15 100 15
1 4 25 200 20
2 1 20 200 20
2 3 10 100 30
2 4 15 100 15
3 1 20 200 20
3 2 15 100 15
3 4 10 100 30
4 1 10 100 30
4 2 20 200 20
4 3 20 200 20
1 90
```
