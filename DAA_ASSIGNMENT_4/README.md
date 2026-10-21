# DAA Assignment 4: Dijkstra - detailed emergency routes

Prints roads, each finalized node and successful relaxations, distances and parents for all nodes, destination route and cumulative leg costs. Sample cost is 10 initially and 5 after updating road 2-3 to cost 1.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "Dijkstra's .cpp" -o Assignment4.exe
.\Assignment4.exe
```

Use the saved input:

```powershell
Get-Content input.txt | .\Assignment4.exe
```

## Input

First line: nodes connections. Then from to nonnegativeCost for each undirected road. Then source destination (zero-based IDs). Y introduces an update row from to newCost; N finishes.

## Output

`Output.txt` is the actual captured output of the current program and saved input. The PDF contains the assignment write-up and pseudocode. Detailed program results are kept in the text output file on GitHub; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

O(V^2) per run and O(V^2) matrix storage; maximum 1,000 nodes.

## Viva notes and scope

Requires nonnegative weights, including updates. A selected hospital/destination is entered manually. No GPS or live feed is connected. Output.txt is current; output.png is a historical screenshot.

## Saved sample input

```text
5 7
0 1 4
0 2 2
1 2 1
1 3 5
2 3 8
2 4 10
3 4 2
0 4
Y
2 3 1
N
```
