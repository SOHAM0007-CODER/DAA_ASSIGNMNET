# DAA Assignment 5: Multistage DP - route details and closures

Prints the network road table, per-city best remaining values, route and each leg's base time, traffic/weather delays, fuel and cost. Demonstrates fastest and cheapest requests, rerouting after a closure and no-route handling.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "SwiftCargo.cpp" -o Assignment5.exe
.\Assignment5.exe
```

Use the saved input:

```powershell
Get-Content input.txt | .\Assignment5.exe
```

## Input

Read cities stages; stage per city; fuel price; road count; roads as from to baseTime trafficDelay weatherDelay fuel open. Menu 1=batch, 2=update, 3=show roads, 0=exit. City IDs start at 1. Each road advances exactly one stage.

## Output

`Output.txt` is the actual captured output of the current program and saved input. The PDF contains the assignment write-up and pseudocode. Detailed program results are kept in the text output file on GitHub; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

O(V+E) per request and O(V+E) network storage. A batch of Q independent requests costs O(Q(V+E)).

## Viva notes and scope

The sample fastest route via city 2 takes 12 minutes and costs 400 INR; cheapest via city 3 takes 16 minutes and costs 200 INR. Manual closures change later requests. There is no shared fleet-capacity model or live traffic connection.

## Saved sample input

```text
4 3
1 2 2 3
100
4
1 2 5 1 0 2 1
1 3 8 0 0 1 1
2 4 5 0 1 2 1
3 4 8 0 0 1 1
3
1
2
1 4 1
1 4 2
2
1
5 1 0 2 0
1
1
1 4 1
2
2
8 0 0 1 0
1
1
1 4 1
0
```
