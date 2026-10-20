# Assignment 8: SwiftShip Demo

## Compile and run

In Windows PowerShell, inside the assignment folder:

```powershell
g++ -std=c++11 SwiftShipTSP.cpp -o SwiftShipTSP.exe
.\SwiftShipTSP.exe
```

To edit in Vim, use `vim SwiftShipTSP.cpp`, then Esc and `:wq`.
On Linux/WSL, compile with `-o SwiftShipTSP` and run `./SwiftShipTSP`.

## Demo A: Minimum fuel cost within 90 minutes

Enter the following values in order:

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

Meaning:
- 4 cities, identified by 1, 2, 3 and 4.
- Fuel costs 100 INR per litre.
- 12 directed roads; all ordered city pairs are present in this example.
- Each road is `from to distanceKm fuelMlPerKm travelMinutes`.
- Start at city 1 and finish the complete tour within 90 minutes.

For example, the road `1 4 25 200 20` is 25 km, with a fuel consumption
rate of 200 mL/km and travel time 20 minutes. It uses 5 litres, costing
500 INR. This higher consumption rate illustrates a less efficient road.

Expected output:

```text
Optimal route: 1 -> 3 -> 2 -> 4 -> 1
Minimum fuel cost: 550.000 INR
Total distance: 55 km
Total fuel: 5.500 litres
Total travel time: 75 minutes
Time limit: 90 minutes
Optimality proven by LC Branch and Bound.
```

Check the selected route:

| Road | Distance | Fuel | Cost | Minutes |
| --- | --- | --- | --- | --- |
| 1 -> 3 | 15 km | 1.5 litres | 150 INR | 15 |
| 3 -> 2 | 15 km | 1.5 litres | 150 INR | 15 |
| 2 -> 4 | 15 km | 1.5 litres | 150 INR | 15 |
| 4 -> 1 | 10 km | 1 litre | 100 INR | 30 |
| Total | 55 km | 5.5 litres | 550 INR | 75 |

The truck visits every city once and returns to the start. The return road
is included in the duration and cost. Search statistics appear after these
results; they may differ if the code's tie-breaking is changed.

## Demo B: Relax the time limit

Restart with the same roads, but change the final line to:

```text
1 130
```

Expected output:

```text
Optimal route: 1 -> 2 -> 3 -> 4 -> 1
Minimum fuel cost: 400.000 INR
Total distance: 40 km
Total fuel: 4.000 litres
Total travel time: 120 minutes
Time limit: 130 minutes
Optimality proven by LC Branch and Bound.
```

Explain: the cheaper route takes 120 minutes. It was invalid in the
90-minute demo but is allowed now. Zero expanded nodes can be correct:
the greedy seed is feasible and its cost already equals the root lower
bound, proving no cheaper tour is possible.

## Demo C: No feasible tour

Restart with the same roads and final line:

```text
1 70
```

Expected result:

```text
No tour visits every city and returns within the time limit.
```

The fastest complete tour needs 75 minutes, so a 70-minute limit is impossible.

## Points to explain
- TSP requires one visit to each city and a final return to the starting city.
- Road condition is represented by the entered fuel-consumption rate.
- The objective is minimum fuel expense subject to a total-time deadline.
- LC means expand the live route with the least lower bound using a priority queue.
- Lower bound = incurred cost + max(outgoing-minimum sum, incoming-minimum sum).
- Separate time bounds prune routes that cannot meet the deadline.
- Greedy tours only initialize an upper bound. Branch and Bound proves optimality.
- Costs are stored in milli-INR, using integers so pruning is exact.
- The search can remain factorial in the worst case; pruning effectiveness
  depends on the particular graph and deadline.

## Screenshots and file input

Run demos A-C interactively and capture the entered values and final output.
Alternatively:

```powershell
Get-Content input.txt | .\SwiftShipTSP.exe
```

File redirection does not echo input values, so prompts can appear together.
Output.txt contains the captured 90-minute demo run. For other limits, edit the final line of input.txt and rerun.
